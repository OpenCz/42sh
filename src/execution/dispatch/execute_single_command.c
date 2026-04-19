/*
** EPITECH PROJECT, 2026
** execute
** File description:
** single command
*/

#include "c_zsh.h"

int execute_single_command(main_t *stock_main,
    char *command, bool allow_builtin)
{
    command_ctx_t ctx;
    int parse_status = parse_command_context(command, &ctx, stock_main);
    int builtin_status = -1;

    if (parse_status == 1)
        return 1;
    if (parse_status == 2)
        return SUCCESS;
    if (allow_builtin) {
        builtin_status = execute_builtin(stock_main, &ctx);
        if (builtin_status != -1) {
            clear_command_ctx(&ctx);
            return builtin_status;
        }
    }
    builtin_status = exec_any(stock_main, &ctx);
    clear_command_ctx(&ctx);
    return builtin_status;
}
