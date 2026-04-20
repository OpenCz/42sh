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
    char **arr = my_str_to_word_array(file, "\n");
    int len = 0;
    int tmp = 0;

    if (!arr)
        return;
    len = my_wordarray_len(arr);
    if (n > len)
        n = len;
    for (int i = len - n; tmp < n && arr[i] != NULL; i++) {
        printf("%s\n", arr[i]);
        tmp++;
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
