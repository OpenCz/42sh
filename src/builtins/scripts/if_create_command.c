/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** if
*/

#include "../../../include/c_zsh.h"

static void check_array(char *str, int *start, int *end)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '(')
            *start += 1;
        if (str[i] == ')')
            *end += 1;
    }
}

int is_valid_formating(char **arr)
{
    int start = 0;
    int end = 0;

    for (int i = 0; arr[i]; i++) {
        check_array(arr[i], &start, &end);
        if (strcmp(arr[i], "else") == 0 && !arr[i + 1]) {
            printf("if: Expression Syntax.\n");
            return -1;
        }
    }
    if (start == end)
        return 0;
    if (start > end)
        printf("Too many ('s\n");
    else
        printf("Too many )'s\n");
    return -1;
}

char *append_buffer(command_ctx_t *ctx, int *i)
{
    char *buffer = calloc(1, BUFFER_SIZE);

    if (!buffer)
        return NULL;
    buffer = strcpy(buffer, ctx->argv[*i]);
    for (; ctx->argv[*i + 1] && strcmp(ctx->argv[*i + 1], "else") &&
        (!is_command(ctx->argv[*i]) &&
            !is_command(ctx->argv[*i + 1])); *i += 1) {
        buffer = strcat(buffer, " ");
        buffer = strcat(buffer, ctx->argv[*i + 1]);
    }
    *i += 2;
    return buffer;
}

static char *verif_value(main_t *main, char **str)
{
    if (!is_command(*str))
        sprintf(*str, "%d", redirect_command(main, *str));
    return *str;
}

static int is_else_condition(command_ctx_t *ctx)
{
    for (int i = 0; ctx->argv[i]; i++)
        if (strcmp("else", ctx->argv[i]) == 0)
            return 1;
    return 0;
}

char *create_condition(main_t *main, command_ctx_t *ctx,
    char **else_cmd, char **to_exec)
{
    char *buffer = calloc(1, BUFFER_SIZE);
    int i = 1;
    int is_else = is_else_condition(ctx);

    if (!buffer)
        return NULL;
    for (; ctx->argv[i + 1] &&
        strcmp(ctx->argv[i + 1], "endif") != 0; i++) {
        if (!is_command(ctx->argv[i]) && !is_command(ctx->argv[i + 1]))
            break;
        buffer = strcat(buffer, verif_value(main, &ctx->argv[i]));
    }
    *to_exec = append_buffer(ctx, &i);
    if (is_else)
        *else_cmd = append_buffer(ctx, &i);
    return buffer;
}
