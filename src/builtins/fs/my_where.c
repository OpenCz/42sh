/*
** EPITECH PROJECT, 2026
** which
** File description:
** which
*/

#include "c_zsh.h"

static int is_shell_builtin(char *name)
{
    if (my_strcmp(name, "env") == 0 || my_strcmp(name, "setenv") == 0)
        return 1;
    if (my_strcmp(name, "unsetenv") == 0 || my_strcmp(name, "cd") == 0)
        return 1;
    if (my_strcmp(name, "jobs") == 0 || my_strcmp(name, "fg") == 0)
        return 1;
    if (my_strcmp(name, "bg") == 0 || my_strcmp(name, "repeat") == 0)
        return 1;
    if (my_strcmp(name, "which") == 0 || my_strcmp(name, "where") == 0)
        return 1;
    if (my_strcmp(name, "printenv") == 0 || my_strcmp(name, "history") == 0)
        return 1;
    return 0;
}

static int print_paths_for_command(main_t *main_stock, char *command)
{
    char *bin_place = NULL;
    int found = 0;

    for (int i = 0; main_stock->path[i] != NULL; i++) {
        bin_place = check_bin(command, main_stock->path[i]);
        if (bin_place != NULL) {
            printf("%s\n", bin_place);
            free_alloc(bin_place);
            found = 1;
        }
    }
    return found;
}

static int print_not_found(char *command)
{
    my_putstrerror(command);
    my_putstrerror(": Command not found.\n");
    return 0;
}

static int print_where_result(main_t *main_stock, char *command)
{
    int found = print_paths_for_command(main_stock, command);

    if (is_shell_builtin(command)) {
        printf("%s: shell built-in command.\n", command);
        found = 1;
    }
    if (!found)
        return print_not_found(command);
    return SUCCESS;
}

int builtin_where(main_t *main_stock, command_ctx_t *ctx)
{
    int status = 0;

    if (ctx->arg_command[0] == NULL) {
        my_putstrerror("where: Too few arguments.\n");
        return 1;
    }
    for (int i = 0; ctx->arg_command[i] != NULL; i++)
        status |= print_where_result(main_stock, ctx->arg_command[i]);
    return status;
}
