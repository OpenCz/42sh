/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** unsetenv builtin: find_env_node locates the node by key
** with a prev pointer; remove_env_node splices it out of
** the list and frees key, value and the node struct.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include "c_zsh.h"

env_t *find_env_node(env_t *env, char *key, env_t **prev)
{
    *prev = NULL;
    while (env && my_strcmp(env->key, key) != 0) {
        *prev = env;
        env = env->next;
    }
    return env;
}

void remove_env_node(env_t **env, env_t *curr, env_t *prev)
{
    if (prev)
        prev->next = curr->next;
    else
        *env = curr->next;
    free(curr->key);
    free(curr->value);
    free(curr);
}

int builtin_unsetenv(main_t *main_stock, command_ctx_t *ctx)
{
    env_t *curr;
    env_t *prev;
    char *key;

    key = ctx->arg_command[0];
    if (!key)
        return 1;
    curr = find_env_node(main_stock->stock_env, key, &prev);
    if (!curr)
        return SUCCESS;
    remove_env_node(&main_stock->stock_env, curr, prev);
    return SUCCESS;
}

int my_unsetenv(main_t *main_stock)
{
    command_ctx_t ctx = {0};

    ctx.arg_command = main_stock->arg_command;
    return builtin_unsetenv(main_stock, &ctx);
}
