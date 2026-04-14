/*
** EPITECH PROJECT, 2026
** redirection
** File description:
** redirection
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
