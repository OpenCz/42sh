/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Hard-coded variable resolution ($0, $?, $$)
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

char *is_hard(const char *key, size_t key_len, main_t *stock_main)
{
    char *pid = NULL;
    char *hard_keys[] = {"0", "?", "$", NULL};
    char *hard_values[4];

    pid = malloc(32);
    if (!pid)
        return NULL;
    snprintf(pid, 32, "%d", getpid());
    hard_values[0] = "c_zsh";
    hard_values[1] = stock_main->last_exit;
    hard_values[2] = pid;
    hard_values[3] = NULL;
    for (int i = 0; hard_keys[i]; i++) {
        if (strlen(hard_keys[i]) == key_len &&
            strncmp(hard_keys[i], key, key_len) == 0) {
            if (i != 2)
                free(pid);
            return hard_values[i];
            }
    }
    free(pid);
    return NULL;
}
