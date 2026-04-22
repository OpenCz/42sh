/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** manage_prompt
*/

#include "../../include/c_zsh.h"

static int get_b_color(char *color)
{
    char *colors[] = {"black", "red", "green", "yellow",
        "blue", "magenta", "cyan", "white", "gray"};
    int int_colors[] = {BG_BLACK, BG_RED, BG_GREEN, BG_YELLOW,
        BG_BLUE, BG_MAGENTA, BG_CYAN, BG_WHITE, BG_GRAY};

    for (int i = 0; colors[i]; i++) {
        if (my_strcmp(colors[i], color) == 0)
            return int_colors[i];
    }
    return DEFAULT;
}

static int get_color(char *color)
{
    char *colors[] = {"black", "red", "green", "yellow",
        "blue", "magenta", "cyan", "white", "gray"};
    int int_colors[] = {FG_BLACK, FG_RED, FG_GREEN, FG_YELLOW,
        FG_BLUE, FG_MAGENTA, FG_CYAN, FG_WHITE, FG_GRAY};

    for (int i = 0; colors[i]; i++) {
        if (my_strcmp(colors[i], color) == 0)
            return int_colors[i];
    }
    return DEFAULT;
}

static void manage_format(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ":");
    char *formats_str[] = {"LONG", "EU", "US", "ISO"};
    date_format_t formats[] = {LONG, EU, US, ISO};

    if (!user_infos)
        return;
    for (int i = 0; formats_str[i]; i++) {
        if (my_strcmp(formats_str[i], user_infos[0]) == 0)
            rc->prompt->date_format = formats[i];
    }
}

static void manage_time(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ":");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->time.toggle = true;
    rc->prompt->time.color = get_color(user_infos[1]);
    rc->prompt->time.b_color = get_b_color(user_infos[2]);
}

static void manage_date(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ":");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->date.toggle = true;
    rc->prompt->date.color = get_color(user_infos[1]);
    rc->prompt->date.b_color = get_b_color(user_infos[2]);
}

static void manage_branche(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ":");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->git_branch.toggle = true;
    rc->prompt->git_branch.color = get_color(user_infos[1]);
    rc->prompt->git_branch.b_color = get_b_color(user_infos[2]);
}

static void manage_folder(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ":");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->folder.toggle = true;
    rc->prompt->folder.color = get_color(user_infos[1]);
    rc->prompt->folder.b_color = get_b_color(user_infos[2]);
}

static void manage_user(czshrc_t *rc, char *infos)
{
    char **user_infos = my_str_to_word_array(infos, ":");

    if (!user_infos)
        return;
    if (my_strcmp(user_infos[0], "true") == 0)
        rc->prompt->user.toggle = true;
    rc->prompt->user.color = get_color(user_infos[1]);
    rc->prompt->user.b_color = get_b_color(user_infos[2]);
}

static void redirect_infos(czshrc_t *rc, char ***rc_parsed, int i)
{
    char *infos[] = {"user", "folder", "git_branch", "date", "time",
        "date_format"};
    void (*fcall[])(czshrc_t *rc, char *infos) = {manage_user, manage_folder,
        manage_branche, manage_date, manage_time, manage_format};

    for (int j = 0; infos[j]; j++) {
        if (my_strcmp(rc_parsed[i][0], infos[j]) == 0)
            fcall[j](rc, rc_parsed[i][1]);
    }
}

void manage_prompt(czshrc_t *rc, char ***rc_parsed, int i)
{
    rc->prompt = malloc(sizeof(prompt_t));
    if (!rc->prompt)
        return;
    for (; rc_parsed[i] != NULL &&
        my_strcmp(rc_parsed[i][0], "[alias]") == 0; i++) {
        if (rc_parsed[i][0][0] == '#')
            continue;
        redirect_infos(rc, rc_parsed, i);
    }
}
