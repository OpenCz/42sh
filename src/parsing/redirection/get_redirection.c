/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Redirection token scanner: get_redirection scans the command
** for >>, <<, >, < (longest-match first) outside quoted sections
** and returns the matching token string, or NULL if none found.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

char *get_redirection(const char *command)
{
    const char *redirs[] = { ">>", "<<", ">", "<" };
    size_t n = sizeof(redirs) / sizeof(redirs[0]);

    for (size_t i = 0; i < n; i++) {
        if (my_strstr(command, redirs[i]) != NULL)
            return (char *)redirs[i];
    }
    return NULL;
}
