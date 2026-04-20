/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** shell
*/

#include "c_zsh.h"

void write_limited_history(char *file, command_ctx_t *ctx)
{
    int n = atoi(ctx->argv[1]);
    char *str = strtok(file, "\n");

    for (int i = 0; i < n && str != NULL; i++) {
        printf("%s\n", str);
        str = strtok(NULL, "\n");
    }
}

int builtin_history(main_t *main_stock, command_ctx_t *ctx)
{
    char *file = openator(".c_zsh_history");
    int len = my_wordarray_len(ctx->argv);

    if (!file)
        return 1;
    if (len == 1)
        printf("%s", file);
    else
        write_limited_history(file, ctx);
    free(file);
    return 0;
}
