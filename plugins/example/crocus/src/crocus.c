/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/plugins
** File description:
** tic-tac-toe.c
*/

#include "c_zsh.h"
#include "../include/crocus.h"
#include <stdio.h>

int len_array(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}

void append_array(char ***array, char *name)
{
    char **new_array = NULL;
    int len = len_array(*array);

    if (!(*array)) {
        *array = malloc(sizeof(char *) * 2);
        if (!*array)
            return;
        (*array)[0] = strdup(name);
        (*array)[1] = NULL;
    } else {
        new_array = realloc(*array, sizeof(char *) * (len + 2));
        if (!new_array)
            return;
        *array = new_array;
        (*array)[len] = strdup(name);
        (*array)[len + 1] = NULL;
    }
}

void append_array_to_array(char ***array, char **array2)
{
    char **new_array = NULL;
    int idx = 0;
    int len_array1 = len_array(*array);
    int len_array2 = len_array(array2);

    if (!array2)
        return;
    if (!(*array)) {
        *array = array2;
        return;
    }
    new_array = realloc(*array, sizeof(char *) * (len_array1 + len_array2 + 1));
    if (!new_array)
        return;
    *array = new_array;
    for (; array2[idx] != NULL; idx++)
        (*array)[len_array1 + idx] = array2[idx];
    (*array)[len_array1 + idx] = NULL;
}

static int crocus_builtin(main_t *main_stock, command_ctx_t *ctx)
{
    char **av = NULL;
    int argc = len_array(ctx->arg_command);

    (void)main_stock;
    av = malloc(sizeof(char *) * (argc + 2));
    if (!av)
        return 84;
    av[0] = strdup("./crocus");
    if (!av[0]) {
        free(av);
        return 84;
    }
    for (int i = 0; i < argc; i++)
        av[i + 1] = ctx->arg_command[i];
    av[argc + 1] = NULL;
    crocus(argc + 1, av);
    free(av[0]);
    free(av);
    return 0;
}

int czsh_plugin_init(main_t *main_stock, const shell_plugin_api_t *api)
{
    if (!api || api->abi_version != CZSH_PLUGIN_ABI_VERSION)
        return CZSH_PLUGIN_ERR;
    if (!api->register_builtin)
        return CZSH_PLUGIN_ERR;
    return api->register_builtin(main_stock, "crocus", crocus_builtin,
        api->plugin_handle);
}

void czsh_plugin_shutdown(main_t *main_stock)
{
    (void)main_stock;
}
