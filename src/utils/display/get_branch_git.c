/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The get_branch_git.c
*/

#include "c_zsh.h"

char *get_branch_git(void)
{
    char *new_str = NULL;
    char *str = NULL;

    if (access(".git/HEAD", F_OK) == -1)
        return str;
    str = openator(".git/HEAD");
    if (my_strncmp(str, "ref: refs/heads/", 16) == 0)
        new_str = my_strdup(str + 16);
    if (!new_str) {
        free(str);
        return NULL;
    }
    free(str);
    new_str[my_strlen(new_str) - 1] = '\0';
    return new_str;
}
