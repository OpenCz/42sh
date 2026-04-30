/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Prompt configuration parser: get_color/get_b_color convert
** color name strings to ANSI codes; manage_format, manage_time,
** manage_date, manage_branche, manage_folder, manage_user fill
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../include/c_zsh.h"

static int get_b_color(char *color)
{
    char *colors[] = {"black", "red", "green", "yellow", "blue", "magenta",
        "cyan", "white", "gray", "bright_red", "bright_green",
        "bright_yellow", "bright_blue", "bright_magenta", "bright_cyan",
        "bright_white", "pink", "rose", "peach", "orange", "pale_yellow",
        "mint", "spring_green", "sky", "light_blue", "lavender", "purple",
        "soft_gray", "light_gray", NULL};
    int int_colors[] = {BG_BLACK, BG_RED, BG_GREEN, BG_YELLOW, BG_BLUE,
        BG_MAGENTA, BG_CYAN, BG_WHITE, BG_GRAY, BG_BRIGHT_RED,
        BG_BRIGHT_GREEN, BG_BRIGHT_YELLOW, BG_BRIGHT_BLUE, BG_BRIGHT_MAGENTA,
        BG_BRIGHT_CYAN, BG_BRIGHT_WHITE, BG_PINK, BG_ROSE, BG_PEACH,
        BG_ORANGE, BG_PALE_YELLOW, BG_MINT, BG_SPRING_GREEN, BG_SKY,
        BG_LIGHT_BLUE, BG_LAVENDER, BG_PURPLE, BG_SOFT_GRAY, BG_LIGHT_GRAY};

    for (int k = 0; color && color[k]; k++)
        color[k] = (char)tolower((unsigned char)color[k]);
    for (int i = 0; colors[i]; i++)
        if (my_strcmp(colors[i], color) == 0)
            return int_colors[i];
    return DEFAULT;
}

static int get_color(char *color)
{
    char *colors[] = {"black", "red", "green", "yellow", "blue", "magenta",
        "cyan", "white", "gray", "bright_red", "bright_green",
        "bright_yellow", "bright_blue", "bright_magenta", "bright_cyan",
        "bright_white", "pink", "rose", "peach", "orange", "pale_yellow",
        "mint", "spring_green", "sky", "light_blue", "lavender", "purple",
        "soft_gray", "light_gray", NULL};
    int int_colors[] = {FG_BLACK, FG_RED, FG_GREEN, FG_YELLOW, FG_BLUE,
        FG_MAGENTA, FG_CYAN, FG_WHITE, FG_GRAY, FG_BRIGHT_RED,
        FG_BRIGHT_GREEN, FG_BRIGHT_YELLOW, FG_BRIGHT_BLUE, FG_BRIGHT_MAGENTA,
        FG_BRIGHT_CYAN, FG_BRIGHT_WHITE, FG_PINK, FG_ROSE, FG_PEACH,
        FG_ORANGE, FG_PALE_YELLOW, FG_MINT, FG_SPRING_GREEN, FG_SKY,
        FG_LIGHT_BLUE, FG_LAVENDER, FG_PURPLE, FG_SOFT_GRAY, FG_LIGHT_GRAY};

    for (int k = 0; color && color[k]; k++)
        color[k] = (char)tolower((unsigned char)color[k]);
    for (int i = 0; colors[i]; i++)
        if (my_strcmp(colors[i], color) == 0)
            return int_colors[i];
    return DEFAULT;
}

static void manage_format(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ": ");
    char *formats_str[] = {"LONG", "EU", "US", "ISO", NULL};
    date_format_t formats[] = {LONG, EU, US, ISO};

    if (!user_infos)
        return;
    for (int i = 0; formats_str[i]; i++)
        if (my_strcmp(formats_str[i], user_infos[0]) == 0)
            rc->prompt->date_format = formats[i];
    free_array(user_infos);
}

static void manage_time(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ": ");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->time.toggle = true;
    if (user_infos[1])
        rc->prompt->time.color = get_color(user_infos[1]);
    if (user_infos[2])
        rc->prompt->time.b_color = get_b_color(user_infos[2]);
    free_array(user_infos);
}

static void manage_date(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ": ");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->date.toggle = true;
    if (user_infos[1])
        rc->prompt->date.color = get_color(user_infos[1]);
    if (user_infos[2])
        rc->prompt->date.b_color = get_b_color(user_infos[2]);
    free_array(user_infos);
}

static void manage_branche(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ": ");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->git_branch.toggle = true;
    if (user_infos[1])
        rc->prompt->git_branch.color = get_color(user_infos[1]);
    if (user_infos[2])
        rc->prompt->git_branch.b_color = get_b_color(user_infos[2]);
    free_array(user_infos);
}

static void manage_folder(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ": ");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->folder.toggle = true;
    if (user_infos[1])
        rc->prompt->folder.color = get_color(user_infos[1]);
    if (user_infos[2])
        rc->prompt->folder.b_color = get_b_color(user_infos[2]);
    free_array(user_infos);
}

static void manage_user(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ": ");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->user.toggle = true;
    if (user_infos[1])
        rc->prompt->user.color = get_color(user_infos[1]);
    if (user_infos[2])
        rc->prompt->user.b_color = get_b_color(user_infos[2]);
    free_array(user_infos);
}

static void redirect_infos(czshrc_t *rc, char ***rc_parsed, int i)
{
    char *infos[] = {"user", "folder", "git_branch", "date", "time",
        "date_format", NULL};
    void (*fcall[])(czshrc_t *rc, char *infos) = {manage_user, manage_folder,
        manage_branche, manage_date, manage_time, manage_format};

    for (int j = 0; infos[j]; j++)
        if (my_strcmp(rc_parsed[i][0], infos[j]) == 0)
            fcall[j](rc, rc_parsed[i][1]);
}

void manage_prompt(czshrc_t *rc, char ***rc_parsed, int i)
{
    for (i++; rc_parsed[i] != NULL &&
        my_strcmp(rc_parsed[i][0], "[alias]") != 0; i++) {
        if (rc_parsed[i][0][0] == '#')
            continue;
        redirect_infos(rc, rc_parsed, i);
    }
}
