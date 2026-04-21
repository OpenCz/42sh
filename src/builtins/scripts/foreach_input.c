/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** foreach_input
*/

#include "../../../include/c_zsh.h"

static char **get_cmd(char **cmd, char *line)
{
    int len = my_wordarray_len(cmd);
    char **new_cmd = realloc(cmd, sizeof(char *) * (len + 2));

    if (new_cmd == NULL)
        return NULL;
    new_cmd[len] = my_strdup(line);
    if (new_cmd[len] == NULL) {
        free_array(new_cmd);
        return NULL;
    }
    new_cmd[len + 1] = NULL;
    return new_cmd;
}

static char **free_getline_data(char **cmd, char *line)
{
    free(line);
    free_array(cmd);
    return NULL;
}

static int append_cmd(char ***cmd, char *line)
{
    char **tmp = get_cmd(*cmd, line);

    if (tmp == NULL)
        return FAILURE;
    *cmd = tmp;
    return SUCCESS;
}

char **foreach_read_commands(void)
{
    size_t len = 0;
    ssize_t read = 0;
    char *line = NULL;
    char **cmd = NULL;

    while (1) {
        my_putstr("foreach? ");
        read = getline(&line, &len, stdin);
        if (read == -1)
            return free_getline_data(cmd, line);
        line[read - 1] = '\0';
        if (my_strcmp(line, "end") == 0)
            break;
        if (append_cmd(&cmd, line) == FAILURE)
            return free_getline_data(cmd, line);
    }
    free(line);
    return cmd;
}
