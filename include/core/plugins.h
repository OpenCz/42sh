/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/include/core
** File description:
** plugins.h
*/

#ifndef PLUGINS_H
    #define PLUGINS_H

    #define CZSH_PLUGIN_ABI_VERSION 1
    #define CZSH_PLUGIN_OK 0
    #define CZSH_PLUGIN_ERR -1

typedef struct main_s main_t;
typedef struct command_ctx_s command_ctx_t;

typedef int (*builtin_func_t)(main_t *main_stock,
    command_ctx_t *ctx);

typedef int (*register_builtin_fn_t)(main_t *main_stock,
    const char *name, builtin_func_t func, void *plugin);

typedef struct shell_plugin_api_s {
    int abi_version;
    register_builtin_fn_t register_builtin;
    void *plugin_handle;
} shell_plugin_api_t;

typedef int (*plugin_init_fn_t)(main_t *main_stock,
    const shell_plugin_api_t *api);

int czsh_plugin_init(main_t *main_stock, const shell_plugin_api_t *api);
void czsh_plugin_shutdown(main_t *main_stock);

#endif
