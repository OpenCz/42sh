/*
** EPITECH PROJECT, 2026
** 42_sh
** File description:
** czshrc
*/

#ifndef __CZ_SHRT_H__
    #define __CZ_SHRT_H__
#include <stdbool.h>

typedef struct infos_s
{
    bool toggle;
    int color;
    int b_color;
} infos_t;

typedef struct prompt_s
{
    infos_t git_branch;
    infos_t folder;
    infos_t user;
    infos_t date;
    infos_t time;
} prompt_t;

#endif
