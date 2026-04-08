/*
** EPITECH PROJECT, 2026
** mycd
** File description:
** mycd
*/

#include "minishell.h"

int my_chdir_call(char *path)
{
    if (chdir(path) == -1) {
        my_putstrerror(path);
        my_putstrerror(": Permission denied.\n");
        return 1;
    }
    return SUCCESS;
}

static char *resolve_path(main_t *main_stock, command_ctx_t *ctx)
{
    char *path = ctx->arg_command[0];

    if (!path || my_strcmp(path, "~") == 0)
        return main_stock->home;
    if (my_strcmp(path, "-") == 0) {
        if (!main_stock->old_path)
            return NULL;
        return main_stock->old_path;
    }
    return path;
}

static int check_path(char *path)
{
    struct stat st;

    if (stat(path, &st) == -1) {
        my_putstrerror(path);
        my_putstrerror(": No such file or directory.\n");
        return 1;
    }
    if (!S_ISDIR(st.st_mode)) {
        my_putstrerror(path);
        my_putstrerror(": Not a directory.\n");
        return 1;
    }
    return SUCCESS;
}

static void save_old_path(main_t *main_stock)
{
    char *cwd = getcwd(NULL, 0);

    if (!cwd)
        return;
    free(main_stock->old_path);
    main_stock->old_path = cwd;
}

int builtin_cd(main_t *main_stock, command_ctx_t *ctx)
{
    char *path = resolve_path(main_stock, ctx);

    if (!path)
        return 1;
    if (check_path(path) == 1)
        return 1;
    path = my_strdup(path);
    save_old_path(main_stock);
    if (my_chdir_call(path) == 1) {
        free(path);
        return 1;
    }
    free(path);
    return SUCCESS;
}

int my_chdir(main_t *main_stock)
{
    command_ctx_t ctx = {0};

    ctx.arg_command = main_stock->arg_command;
    return builtin_cd(main_stock, &ctx);
}
