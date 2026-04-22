/*
** EPITECH PROJECT, 2026
** 42_sh
** File description:
** czshrc
*/

#ifndef CZ_SHRT_H
    #define CZ_SHRT_H

    #include "../c_zsh.h"

typedef enum date_format_e {
    LONG,
    EU,
    US,
    ISO
} date_format_t;

typedef struct infos_s {
    bool toggle;
    int color;
    int b_color;
} infos_t;

typedef struct prompt_s {
    infos_t git_branch;
    infos_t folder;
    infos_t user;
    infos_t date;
    infos_t time;
    date_format_t date_format;
} prompt_t;

typedef struct czshrc_s
{
    prompt_t *prompt;
} czshrc_t;

typedef struct buffer_s {
    int *len;
    char **buffer;
} buffer_t;

void set_default_rc(czshrc_t *rc);
void manage_prompt(czshrc_t *rc, char ***rc_parsed, int i);
czshrc_t *update_rc(void);

#endif
