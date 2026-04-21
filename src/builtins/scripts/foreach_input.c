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

static int handle_bracket(command_ctx_t *ctx)
{
    int len_array = 0;
    int len = 0;

    if (my_wordarray_len(ctx->arg_command) > 2
        && ctx->arg_command[1][0] != '(') {
        my_putstr("foreach: Words not parenthesized.\n");
        return FAILURE;
    }
    if (ctx->arg_command[1] && ctx->arg_command[1][0] != '(') {
        my_putstr("foreach: Too few arguments.\n");
        return FAILURE;
    }
    len_array = my_wordarray_len(ctx->arg_command) - 1;
    len = strlen(ctx->arg_command[len_array]) - 1;
    if (ctx->arg_command[len_array][len] != ')') {
        my_putstr("Too many (\'s.\n");
        return FAILURE;
    }
    return SUCCESS;
}

int handle_error(command_ctx_t *ctx)
{
    if (my_wordarray_len(ctx->arg_command) < 2) {
        my_putstr("foreach: Too few arguments.\n");
        return FAILURE;
    }
    if (my_char_is_alpha(ctx->arg_command[0][0]) == 1) {
        my_putstr("foreach: Variable name must begin with a letter.\n");
        return FAILURE;
    }
    if (my_str_is_alphanum(ctx->arg_command[0]) == 1) {
        my_putstr("foreach: Variable name must contain alphanumeric"
            " characters\n");
        return FAILURE;
    }
    return handle_bracket(ctx);
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
