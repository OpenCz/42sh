/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/var_local
** File description:
** unset
*/

#include "c_zsh.h"

static env_t *find_local_node(env_t *env, char *key, env_t **prev)
{
    *prev = NULL;
    while (env && my_strcmp(env->key, key) != 0) {
        *prev = env;
        env = env->next;
    }
    return env;
}

static void remove_local_node(env_t **env, env_t *curr, env_t *prev)
{
    if (prev)
        prev->next = curr->next;
    else
        *env = curr->next;
    free(curr->key);
    free(curr->value);
    free(curr);
}

int builtin_unset(main_t *main_stock, command_ctx_t *ctx)
{
    env_t *curr;
    env_t *prev;
    char *key;

    key = ctx->arg_command[0];
    if (!key)
        return 1;
    curr = find_local_node(main_stock->stock_local_var, key, &prev);
    if (!curr)
        return SUCCESS;
    remove_local_node(&main_stock->stock_local_var, curr, prev);
    return SUCCESS;
}
