/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Prompt renderer: pwd, username, git each fill an infos_t struct
** with the ANSI-colored component string; display_prompt writes
** each enabled component in order with a reset code at the end.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../../include/c_zsh.h"

static int pwd(char *pwd_folder, infos_t *folder)
{
    int len = 0;

    if (pwd_folder && folder->toggle) {
        my_putstr("\033[");
        my_putnbr(folder->b_color);
        my_putstr("m");
        my_putstr("\033[");
        my_putnbr(folder->color);
        my_putstr("m  ");
        my_putstr(pwd_folder);
        my_putstr(" \033[0m");
        len = my_strlen(pwd_folder) + 4;
        free(pwd_folder);
    }
    return len;
}

static int username(char *user, infos_t *user_info)
{
    int len = 0;

    if (user && user_info->toggle) {
        my_putstr("\033[");
        my_putnbr(user_info->b_color);
        my_putstr("m");
        my_putstr("\033[");
        my_putnbr(user_info->color);
        my_putstr("m  ");
        my_putstr(user);
        len = my_strlen(user) + 4;
        my_putstr(" \033[0m");
    }
    return len;
}

static int git(char *git_branch, infos_t *git_info)
{
    int len = 0;

    if (git_branch && git_info->toggle) {
        my_putstr("\033[");
        my_putnbr(git_info->b_color);
        my_putstr("m");
        my_putstr("\033[");
        my_putnbr(git_info->color);
        my_putstr("m  ");
        my_putstr(git_branch);
        my_putstr(" \033[0m");
        len = my_strlen(git_branch) + 4;
        free(git_branch);
    }
    return len;
}

void display_prompt(prompt_t *prompt, char *user)
{
    char *git_branch = get_branch_git();
    char *pwd_folder = get_folder();

    my_putstr("\033[90m╭─ \033[0m");
    my_putstr("\033[47m\033[30m  \033[0m");
    prompt->len_prompt += 6;
    prompt->len_prompt += pwd(pwd_folder, &prompt->folder);
    prompt->len_prompt += username(user, &prompt->user);
    prompt->len_prompt += git(git_branch, &prompt->git_branch);
    display_time(&prompt->time, &prompt->date, prompt->date_format,
        prompt->len_prompt);
    my_putstr("\n\033[90m╰─\033[0m");
    my_putstr("\033[92m❯\033[0m ");
    prompt->len_prompt = 0;
}
