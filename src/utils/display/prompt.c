/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The prompt.c
*/

#include "c_zsh.h"

static void pwd(char *pwd_folder)
{
    if (pwd_folder) {
        my_putstr("\033[102m  ");
        my_putstr(pwd_folder);
        my_putstr(" \033[0m");
        free(pwd_folder);
    }
}

static void username(char *user)
{
    if (user) {
        my_putstr("\033[103m 🐧 ");
        my_putstr(user);
        my_putstr(" \033[0m");
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

void display_prompt(char *user)
{
    char *git_branch = get_branch_git();
    char *pwd_folder = get_folder();

    display_time();
    my_putstr("\033[");
    my_putnbr(90);
    my_putstr("m");
    my_putstr("╭─ \033[0m");
    my_putstr("\033[47m\033[30m  \033[0m");
    pwd(pwd_folder);
    username(user);
    git(git_branch);
    my_putstr("\n\033[90m╰─❯\033[0m ");
}
