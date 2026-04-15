/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The foreach.c
*/
/**
 * @file foreach.c
 * @brief The foreach.c
 * @author Erwan Lo Presti
 */

#include "../../../include/c_zsh.h"

static int handle_bracket(command_ctx_t *ctx)
{
    int len_array = 0;
    int len = 0;

    if (my_wordarray_len(ctx->arg_command) > 2
        && ctx->arg_command[2][0] != '(') {
        my_putstr("foreach: Words not parenthesized.\n");
        return FAILURE;
    }
    if (ctx->arg_command[1] && ctx->arg_command[1][0] != '(') {
        my_putstr("foreach: Too few arguments.\n");
        return FAILURE;
    }
    len_array = my_wordarray_len(ctx->arg_command) - 1;
    len = strlen(ctx->arg_command[len_array]) - 1;
    if (ctx->arg_command[len_array][len] != ')') {
        my_putstr("Too many (\'s.\n");
        return FAILURE;
    }
    return SUCCESS;
}

static int handle_error(command_ctx_t *ctx)
{
    if (my_wordarray_len(ctx->arg_command) < 2) {
        my_putstr("foreach: Too few arguments.\n");
        return FAILURE;
    }
    if (my_char_is_alpha(ctx->arg_command[0][0]) == 1) {
        my_putstr("foreach: Variable name must begin with a letter.\n");
        return FAILURE;
    }
    if (my_str_is_alphanum(ctx->arg_command[0]) == 1) {
        my_putstr("foreach: Variable name must contain alphanumeric"
            " characters\n");
        return FAILURE;
    }
    return handle_bracket(ctx);
}

int builtin_foreach(main_t *main_stock, command_ctx_t *ctx)
{
    size_t len = 0;
    ssize_t read = 0;
    char *line = NULL;

    if (handle_error(ctx) == FAILURE)
        return FAILURE;
    while (1) {
        my_putstr("foreach? ");
        read = getline(&line, &len, stdin);
        if (read == -1)
            return FAILURE;
        line[read - 1] = '\0';
        if (my_strcmp(line, "end") == 0)
            break;
    }
    free(line);
    return SUCCESS;
}
