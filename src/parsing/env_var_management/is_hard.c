/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Hard-coded variable resolution ($0, $?, $$)
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static char *get_result(char **hard_keys, char **hard_values, const char *key,
    size_t key_len)
{
    char *result = NULL;

    for (int i = 0; hard_keys[i]; i++) {
        if (strlen(hard_keys[i]) == key_len &&
            strncmp(hard_keys[i], key, key_len) == 0) {
            result = hard_values[i];
            break;
        }
    }
    return result;
}

char *is_hard(const char *key, size_t key_len, main_t *stock_main)
{
    char *pid = NULL;
    char *hard_keys[] = {"0", "36", "117 354 889 550", "69", "8",
        "12", "?", "$", NULL};
    char *hard_values[] = {"c_zsh", "Sasha Le Moins-Avalos",
        "Celenzo Peuch", "Lukas Soigneux", "Jessym Gaddacha",
        "Erwan Lo Presti", stock_main ? stock_main->last_exit : "0", NULL};
    char *result = NULL;

    if (!stock_main)
        return NULL;
    pid = my_itoa(getpid());
    if (!pid)
        return NULL;
    hard_values[7] = pid;
    result = get_result(hard_keys, hard_values, key, key_len);
    if (result != pid)
        free(pid);
    return result;
}
