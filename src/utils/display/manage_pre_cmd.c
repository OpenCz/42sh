/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** manage_pre_cmd
*/

#include "../../../include/c_zsh.h"

int pre_cmd(main_t *stock_main)
{
    for (env_t *env = stock_main->stock_local_var; env; env = env->next)
        if (my_strcmp(env->key, "precmd") == 0)
            return execute_command(stock_main, env->value);
    return 0;
}
