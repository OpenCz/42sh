/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The prompt.c
*/
/**
 * @file prompt.c
 * @brief The prompt.c
 * @author Erwan Lo Presti
 */

#include "../../../include/minishell.h"

static void pwd(char *pwd_folder)
{
    if (pwd_folder) {
        my_putstr("\033[102m  ");
        my_putstr(pwd_folder);
        my_putstr(" \033[0m");
        free(pwd_folder);
    }
}

static void git(char *git_branch)
{
    if (git_branch) {
        my_putstr("\033[104m  ");
        my_putstr(git_branch);
        my_putstr(" \033[0m");
        free(git_branch);
    }
}

void display_prompt(void)
{
    char *git_branch = get_branch_git();
    char *pwd_folder = get_folder();

    my_putstr("\033[90m╭─\033[0m ");
    pwd(pwd_folder);
    git(git_branch);
    my_putstr("\n\033[90m╰─❯\033[0m ");
}
