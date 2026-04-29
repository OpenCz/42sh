/*
** EPITECH PROJECT, 2026
** ~/Epitech/Project/42sh/src/builtins/var_local
** File description:
** set
*/

#include "c_zsh.h"

static int free_local_var(env_t *stock)
{
    if (stock->key)
        free(stock->key);
    if (stock->value)
        free(stock->value);
    free(stock);
    return FAILURE;
}

static int change_value(env_t *tmp, char *value)
{
    char *new_value = my_strdup(value);

    if (!new_value)
        return FAILURE;
    free(tmp->value);
    tmp->value = new_value;
    return SUCCESS;
}

static int update_value(env_t *stock, char *key, char *value)
{
    for (env_t *tmp = stock; tmp; tmp = tmp->next) {
        if (my_strcmp(tmp->key, key) == 0)
            return change_value(tmp, value);
    }
    return FAILURE;
}

static env_t *create_local_var(char *key, char *value)
{
    env_t *new = malloc(sizeof(env_t));

    if (!new)
        return NULL;
    new->key = my_strdup(key);
    new->value = my_strdup(value);
    new->next = NULL;
    if (!new->key || !new->value) {
        free_local_var(new);
        return NULL;
    }
    return new;
}

static int push_back(env_t **stock, char *key, char *value)
{
    env_t *new = NULL;
    env_t *tmp = NULL;

    if (*stock && update_value(*stock, key, value) == SUCCESS)
        return SUCCESS;
    new = create_local_var(key, value);
    if (!new)
        return FAILURE;
    if (!*stock) {
        *stock = new;
        return SUCCESS;
    }
    tmp = *stock;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new;
    return SUCCESS;
}

static int is_equal(command_ctx_t *ctx, main_t *main_stock)
{
    int i = 0;
    char *var = NULL;

    for (; ctx->arg_command[i]; i++) {
        var = strchr(ctx->arg_command[i], '=');
        if (var)
            break;
    }
    if (!var) {
        push_back(&main_stock->stock_local_var, ctx->arg_command[0], "");
        return FAILURE;
    }
    return SUCCESS;
}

int builtin_set(main_t *main_stock, command_ctx_t *ctx)
{
    char **var = NULL;

    if (!ctx->arg_command[0])
        return SUCCESS;
    if (is_equal(ctx, main_stock) == FAILURE)
        return SUCCESS;
    if (my_wordarray_len(ctx->arg_command) == 1) {
        var = my_str_to_word_array(ctx->arg_command[0], "=");
        if (!var)
            return FAILURE;
        push_back(&main_stock->stock_local_var, var[0], var[1] ? var[1] : "");
        free_array(var);
        return SUCCESS;
    }
    return push_back(&main_stock->stock_local_var, ctx->arg_command[0],
        ctx->arg_command[2] ? ctx->arg_command[2] : "");
}
