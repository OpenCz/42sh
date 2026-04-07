/*
** EPITECH PROJECT, 2026
** setenv
** File description:
** setenv
*/

#include "minishell.h"

static int update_env_node(env_t *node, char *value)
{
    free(node->value);
    node->value = value ? my_strdup(value) : NULL;
    if (value && !node->value)
        return 1;
    return 0;
}

static env_t *create_new_node(char *key, char *value)
{
    env_t *node = malloc(sizeof(env_t));

    if (!node)
        return NULL;
    node->key = my_strdup(key);
    node->value = value ? my_strdup(value) : NULL;
    node->next = NULL;
    return node;
}

static void push_back(env_t **env, env_t *new_node)
{
    env_t *current = *env;

    if (!*env) {
        *env = new_node;
        return;
    }
    while (current->next)
        current = current->next;
    current->next = new_node;
}

static int error_handling(char *key, char *value, command_ctx_t *ctx)
{
    if (my_wordarray_len(ctx->arg_command) > 2) {
        my_putstrerror("setenv: Too many arguments.\n");
        return 1;
    }
    if (!key)
        return 1;
    if (my_char_isnum(key) == 1) {
        my_putstrerror("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (my_str_is_alphanum(key) == 1) {
        my_putstrerror("setenv: Variable name must ");
        my_putstrerror("contain alphanumeric characters.\n");
        return 1;
    }
    return 0;
}

int builtin_setenv(main_t *main_stock, command_ctx_t *ctx)
{
    env_t *prev;
    env_t *curr;
    char *key = ctx->arg_command[0] ? ctx->arg_command[0] : NULL;
    char *value = ctx->arg_command[1] ? ctx->arg_command[1] : "";

    if (!key)
        return my_env(main_stock);
    if (error_handling(key, value, ctx) == 1)
        return 1;
    curr = find_env_node(main_stock->stock_env, key, &prev);
    if (curr)
        return update_env_node(curr, value);
    curr = create_new_node(key, value);
    if (!curr)
        return 1;
    push_back(&main_stock->stock_env, curr);
    return 0;
}

int my_setenv(main_t *main_stock)
{
    command_ctx_t ctx = {0};

    ctx.arg_command = main_stock->arg_command;
    return builtin_setenv(main_stock, &ctx);
}
