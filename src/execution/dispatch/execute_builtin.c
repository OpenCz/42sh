/*
** EPITECH PROJECT, 2026
** execute
** File description:
** builtin
*/

#include "minishell.h"

const builtin_command_t command_shell[] = {
    {"env", builtin_env},
    {"setenv", builtin_setenv},
    {"unsetenv", builtin_unsetenv},
    {"cd", builtin_cd},
    {NULL, NULL}
};

int execute_builtin(main_t *main_stock, command_ctx_t *ctx)
{
    char *cmd = ctx->command;

    for (size_t i = 0; command_shell[i].name != NULL; i++) {
        if (my_strcmp(cmd, (char *)command_shell[i].name) == 0)
            return command_shell[i].func(main_stock, ctx);
    }
    return -1;
}
