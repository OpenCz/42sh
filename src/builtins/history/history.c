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
    free_array(arr);
}

static void history_reverse(char *file, command_ctx_t *ctx)
{
    int n = atoi(ctx->argv[2]);
    char *str = strtok(file, "\n");

    for (int i = 0; i < n && str; i++) {
        printf("%s\n", str);
        str = strtok(NULL, "\n");
    }
}

int builtin_history(main_t *main_stock, command_ctx_t *ctx)
{
    char *file = openator(".c_zsh_history");

    if (!file)
        return 1;
    if (ctx->argv[1] && strcmp(ctx->argv[1], "-r") == 0) {
        history_reverse(file, ctx);
    } else
        write_limited_history(file, ctx);
    free(file);
    return 0;
}
