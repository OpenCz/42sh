/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Default RC initializer: set_default_prompt enables folder,
** branch, user and time flags with built-in ANSI color codes;
** set_default_rc allocates prompt_t and calls set_default_prompt.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "../../include/c_zsh.h"

static void set_default_prompt(czshrc_t *rc)
{
    rc->prompt = malloc(sizeof(prompt_t));
    if (!rc->prompt)
        return;
    rc->prompt->date.toggle = false;
    rc->prompt->date.color = DEFAULT;
    rc->prompt->date.b_color = DEFAULT;
    rc->prompt->folder.toggle = false;
    rc->prompt->folder.color = DEFAULT;
    rc->prompt->folder.b_color = DEFAULT;
    rc->prompt->git_branch.toggle = false;
    rc->prompt->git_branch.color = DEFAULT;
    rc->prompt->git_branch.b_color = DEFAULT;
    rc->prompt->time.toggle = false;
    rc->prompt->time.color = DEFAULT;
    rc->prompt->time.b_color = DEFAULT;
    rc->prompt->user.toggle = false;
    rc->prompt->user.color = DEFAULT;
    rc->prompt->user.b_color = DEFAULT;
    rc->prompt->date_format = LONG;
    rc->prompt->len_prompt = 0;
}

void set_default_rc(czshrc_t *rc)
{
    set_default_prompt(rc);
}
