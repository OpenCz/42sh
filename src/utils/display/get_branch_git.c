/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Git branch detector: opens .git/HEAD with openator(), extracts
** the name after 'ref: refs/heads/', strips the newline.
** Returns NULL when not inside a git repository.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

static char *free_value(char *value)
{
    if (value)
        free(value);
    return NULL;
}

char *get_branch_git(void)
{
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    fp = popen("git rev-parse --abbrev-ref HEAD 2>/dev/null", "r");
    if (!fp)
        return NULL;
    read = getline(&line, &len, fp);
    pclose(fp);
    if (read <= 0)
        return free_value(line);
    if (line[read - 1] == '\n')
        line[read - 1] = '\0';
    if (strcmp(line, "HEAD") == 0)
        return free_value(line);
    return line;
}
