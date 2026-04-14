/*
** EPITECH PROJECT, 2026
** exec
** File description:
** exec
*/

#include "c_zsh.h"

static char *make_env_entry(char *key, char *value)
{
    char *tmp = my_strconcat(key, "=");
    char *entry = my_strconcat(tmp, value ? value : "");

    free(tmp);
    return entry;
}

static char **build_env(env_t *stock_env)
{
    int count = 0;
    env_t *tmp = stock_env;
    char **env;
    int i = 0;

    for (; tmp; tmp = tmp->next)
        count++;
    env = malloc(sizeof(char *) * (count + 1));
    if (!env)
        return NULL;
    for (; stock_env; stock_env = stock_env->next) {
        env[i] = make_env_entry(stock_env->key, stock_env->value);
        i++;
    }
    env[i] = NULL;
    return env;
}

static void free_env(char **env)
{
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
}

static int is_direct_path(char *cmd)
{
    for (int i = 0; cmd[i]; i++)
        if (cmd[i] == '/')
            return 1;
    return SUCCESS;
}

static int direct_path_exists(char *path)
{
    struct stat st;

    if (!path)
        return 0;
    return stat(path, &st) == 0;
}

static int command_is_directory(char *command)
{
    struct stat st;

    if (!command)
        return 0;
    if (stat(command, &st) != 0)
        return 0;
    return S_ISDIR(st.st_mode);
}

static char *get_exec_path(main_t *main_stock, command_ctx_t *ctx)
{
    if (is_direct_path(ctx->command)) {
        if (direct_path_exists(ctx->command))
            return ctx->command;
        return NULL;
    }
    return loop_bin(main_stock, ctx->command);
}

static int is_directory(command_ctx_t *ctx)
{
    if (command_is_directory(ctx->command)) {
        my_putstrerror(ctx->command);
        my_putstrerror(": Permission denied.\n");
        return 1;
    }
    return 0;
}

static int is_command_not_found(char *path, char **env, command_ctx_t *ctx)
{
    if (!path) {
        my_putstrerror(ctx->command);
        my_putstrerror(": Command not found.\n");
        free_env(env);
        return 1;
    }
    return 0;
}

int exec_any(main_t *main_stock, command_ctx_t *ctx)
{
    int direct = is_direct_path(ctx->command);
    char *path = NULL;
    char **env = NULL;
    int status = 0;

    if (is_directory(ctx))
        return 1;
    path = get_exec_path(main_stock, ctx);
    env = build_env(main_stock->stock_env);
    if (!env || is_command_not_found(path, env, ctx))
        return 1;
    status = run_fork(main_stock, ctx, path, env);
    if (!direct)
        free(path);
    free_env(env);
    return status;
}
