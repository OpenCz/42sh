/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** history builtin: iterates the history_cmd_t doubly-linked list
** from oldest to newest and prints each entry as:
**   ID  HH:MM  command
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

void write_history(char *file, command_ctx_t *ctx)
{
    char **arr = my_str_to_word_array(file, "\n");
    int len = 0;
    int tmp = 0;
    int n = 0;

    if (!arr)
        return;
    len = my_wordarray_len(arr);
    n = ctx->argv[1] ? atoi(ctx->argv[1]) : len;
    if (n > len)
        n = len;
    for (int i = len - n; tmp < n && arr[i] != NULL; i++) {
        printf("%s\n", arr[i]);
        tmp++;
    }
    free_array(arr);
}

static void write_reverse_history(char *file, command_ctx_t *ctx)
{
    int n = ctx->argv[2] ? atoi(ctx->argv[2]) : HISTORY;
    char *str = strtok(file, "\n");

    for (int i = 0; i < n && str; i++) {
        printf("%s\n", str);
        str = strtok(NULL, "\n");
    }
    free_alloc(str);
}

int builtin_history(main_t *main_stock, command_ctx_t *ctx)
{
    char *file = openator(".c_zsh_history");

    if (!file)
        return 1;
    if (ctx->argv[1] && strcmp(ctx->argv[1], "-r") == 0)
        write_reverse_history(file, ctx);
    else
        write_history(file, ctx);
    free_alloc(file);
    return 0;
}
