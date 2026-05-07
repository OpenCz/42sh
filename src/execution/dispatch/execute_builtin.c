/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Builtin registry and dispatcher: command_shell[] maps command
** name strings to handler pointers; execute_builtin searches
** linearly and calls the match, or returns -1 if not found.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"
#include "../../../include/builtins/builtins.h"

const builtin_command_common_t command_shell[] = {
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"cd", builtin_cd},
    {"jobs", builtin_jobs},
    {"fg", builtin_foreground},
    {"bg", builtin_background},
    {"repeat", builtin_repeat},
    {"foreach", builtin_foreach},
    {"which", builtin_which},
    {"where", builtin_where},
    {"printenv", builtin_printenv},
    {"if", builtin_if},
    {"history", builtin_history},
    {"alias", builtin_alias},
    {"source", source},
    {"set", builtin_set},
    {"unset", builtin_unset},
    {"limit", builtin_limit},
    {"unlimit", builtin_unlimit},
    {NULL, NULL}
};

int execute_builtin(main_t *main_stock, command_ctx_t *ctx)
{
    char *cmd = ctx->command;
    builtin_command_t *load_builtin = main_stock->builtin;

    for (size_t i = 0; command_shell[i].name != NULL; i++)
        if (my_strcmp(cmd, (char *)command_shell[i].name) == 0)
            return command_shell[i].func(main_stock, ctx);
    for (; load_builtin; load_builtin = load_builtin->next)
        if (my_strcmp(cmd, (char *)load_builtin->name) == 0)
            return load_builtin->func(main_stock, ctx);
    return -1;
}
