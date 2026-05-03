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

void print_fg_color(int color)
{
    if (color == DEFAULT)
        return;
    if (color >= COLOR_256_BASE) {
        my_putstr("\033[38;5;");
        my_putnbr(color - COLOR_256_BASE);
    } else {
        my_putstr("\033[");
        my_putnbr(color);
    }
    my_putstr("m");
}

void print_bg_color(int b_color)
{
    if (b_color == DEFAULT)
        return;
    if (b_color >= COLOR_256_BASE) {
        my_putstr("\033[48;5;");
        my_putnbr(b_color - COLOR_256_BASE);
    } else {
        my_putstr("\033[");
        my_putnbr(b_color);
    }
    my_putstr("m");
}

static int pwd(char *pwd_folder, infos_t *folder)
{
    int len = 0;

    if (pwd_folder && folder->toggle) {
        print_bg_color(folder->b_color);
        print_fg_color(folder->color);
        my_putstr("  ");
        my_putstr(pwd_folder);
        my_putstr(" \033[0m");
        len = my_strlen(pwd_folder) + 4;
    }
    free_alloc(pwd_folder);
    return len;
}

static int username(char *user, infos_t *user_info)
{
    int len = 0;

    if (user && user_info->toggle) {
        print_bg_color(user_info->b_color);
        print_fg_color(user_info->color);
        my_putstr("  ");
        my_putstr(user);
        my_putstr(" \033[0m");
        len = my_strlen(user) + 4;
    }
    return len;
}

static int git(char *git_branch, infos_t *git_info)
{
    int len = 0;

    if (git_branch && git_info->toggle) {
        print_bg_color(git_info->b_color);
        print_fg_color(git_info->color);
        my_putstr("  ");
        my_putstr(git_branch);
        my_putstr(" \033[0m");
        len = my_strlen(git_branch) + 4;
    }
    free_alloc(git_branch);
    return len;
}

static char *get_id(void)
{
    char **os_release = NULL;
    char *id = NULL;
    char *name = openator("/etc/os-release");

    if (!name)
        return NULL;
    os_release = my_str_to_word_array(name, "\n");
    free_alloc(name);
    if (!os_release)
        return NULL;
    for (int i = 0; os_release[i]; i++) {
        if (my_strncmp(os_release[i], "ID=", 3) == 0) {
            id = my_strdup(os_release[i] + 3);
            break;
        }
    }
    if (!id)
        id = NULL;
    free_array(os_release);
    return id;
}

static void display_logo_unique(char *logo)
{
    my_putstr("\033[47m\033[30m ");
    my_putstr(logo);
    my_putstr(" \033[0m");
}

static void display_logo(void)
{
    char *logo[17] = {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", NULL};
    char *name[17] = {"arch", "ubuntu", "debian", "nixos", "fedora", "mint",
        "manjaro", "alpine", "rhel", "centos", "opensuse", "kali", "pop",
        "endeavouros", "elementary", "zorin", NULL};
    char *id = get_id();

    if (!id) {
        my_putstr("\033[47m\033[30m  \033[0m");
        return;
    }
    for (int i = 0; name[i]; i++) {
        if (my_strncmp(id, name[i], my_strlen(name[i])) == 0) {
            display_logo_unique(logo[i]);
            free(id);
            return;
        }
    }
    my_putstr("\033[47m\033[30m  \033[0m");
    free(id);
}

void display_prompt(prompt_t *prompt, char *user)
{
    char *git_branch = get_branch_git();
    char *pwd_folder = get_folder();

    my_putstr("\033[90m╭─ \033[0m");
    display_logo();
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
