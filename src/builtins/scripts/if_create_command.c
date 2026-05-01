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

    for (int i = 0; arr[i]; i++)
        check_array(arr[i], &start, &end);
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
