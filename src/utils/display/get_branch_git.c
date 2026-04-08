/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The get_branch_git.c
*/
/**
 * @file get_branch_git.c
 * @brief The get_branch_git.c
 * @author Erwan Lo Presti
 */

#include "../../../include/minishell.h"

char *get_branch_git(void)
{
    char *new_str = NULL;
    char *str = openator(".git/HEAD");

    if (!str)
        return NULL;
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
