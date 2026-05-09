/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/plugins
** File description:
** hello.c
*/

#include "c_zsh.h"
#include <stdio.h>

static int hello_builtin(main_t *main_stock, command_ctx_t *ctx)
{
    (void)main_stock;
    (void)ctx;
    printf("hello from plugin!\n");
    return 0;
}

int czsh_plugin_init(main_t *main_stock, const shell_plugin_api_t *api)
{
    if (!api || api->abi_version != CZSH_PLUGIN_ABI_VERSION)
        return CZSH_PLUGIN_ERR;
    if (!api->register_builtin)
        return CZSH_PLUGIN_ERR;
    return api->register_builtin(main_stock, "hello", hello_builtin,
        api->plugin_handle);
}

void czsh_plugin_shutdown(main_t *main_stock)
{
    (void)main_stock;
}
