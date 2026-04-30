/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Pipe syntax validation: has_pipe_syntax_error scans each '|'
** and checks has_left_command / has_right_command; returns an
** error code with a tcsh message on empty left or right segment.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static int is_blank(char c)
{
    return c == ' ' || c == '\t';
}

static int has_left_command(char *command, int index)
{
    index--;
    while (index >= 0 && is_blank(command[index]))
        index--;
    return index >= 0 && command[index] != '|';
}

static int has_right_command(char *command, int index)
{
    index++;
    while (command[index] && is_blank(command[index]))
        index++;
    return command[index] && command[index] != '|';
}

int has_pipe_syntax_error(char *command)
{
    for (int i = 0; command[i]; i++) {
        if (command[i] != '|')
            continue;
        if (!has_left_command(command, i) || !has_right_command(command, i))
            return 1;
    }
    return SUCCESS;
}
