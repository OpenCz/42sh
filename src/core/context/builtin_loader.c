/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** builtin_loader.c
*/

#include "c_zsh.h"

char **list_plugins(void)
{
    DIR *directory = opendir("plugins");
    char **total = NULL;
    struct dirent *file = NULL;

    if (!directory)
        return NULL;
    for (file = readdir(directory); file != NULL; file = readdir(directory))
        if (strstr(file->d_name, ".so") != NULL)
            append_array(&total, file->d_name);
    if (closedir(directory) == -1) {
        free_array(total);
        return NULL;
    }
    return total;
}

int register_builtin(main_t *main_stock, const char *name, builtin_func_t func,
    void *plugin_handle)
{
    builtin_command_t *entry = malloc(sizeof(builtin_command_t));

    if (!entry)
        return CZSH_PLUGIN_ERR;
    entry->name = strdup(name);
    entry->func = func;
    entry->plugin = plugin_handle;
    entry->next = main_stock->builtin;
    main_stock->builtin = entry;
    return CZSH_PLUGIN_OK;
}

static int load_one_plugin(main_t *main_stock, char *name)
{
    void *plugin = dlopen(name, RTLD_LOCAL | RTLD_NOW);
    plugin_init_fn_t init = NULL;
    char *error = NULL;
    shell_plugin_api_t api = {
        .abi_version = CZSH_PLUGIN_ABI_VERSION,
        .register_builtin = register_builtin,
        .plugin_handle = plugin
    };

    if (!plugin)
        return CZSH_PLUGIN_ERR;
    init = (plugin_init_fn_t)dlsym(plugin, "czsh_plugin_init");
    error = dlerror();
    if (error || !init)
        return CZSH_PLUGIN_ERR;
    if (init(main_stock, &api) != CZSH_PLUGIN_OK)
        return CZSH_PLUGIN_ERR;
    return CZSH_PLUGIN_OK;
}

int plugin_load(main_t *main_stock)
{
    char **names = list_plugins();
    char *full_name = NULL;

    if (!names)
        return CZSH_PLUGIN_OK;
    for (int i = 0; names[i] != NULL; i++) {
        full_name = malloc(sizeof(char) * (strlen(names[i]) + 1 + 8));
        full_name = strcpy(full_name, "plugins/");
        full_name = strcat(full_name, names[i]);
        load_one_plugin(main_stock, full_name);
        free_alloc(full_name);
    }
    free_array(names);
    return CZSH_PLUGIN_OK;
}

int builtin_loader(main_t *main_stock)
{
    main_stock->builtin = NULL;
    return plugin_load(main_stock);
}
