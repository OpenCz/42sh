/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** The foreach.c
*/
/**
 * @file foreach.c
 * @brief The foreach.c
 * @author Erwan Lo Presti
 */

#include "../../../include/c_zsh.h"

static int get_len_arg(command_ctx_t *ctx)
{
    int len = my_wordarray_len(ctx->arg_command);

    if (ctx->arg_command[len - 1]
        && strcmp(ctx->arg_command[len - 1], ")") == 0)
        len--;
    if (ctx->arg_command[1] && strcmp(ctx->arg_command[1], "(") == 0)
        len--;
    return len;
}

static void fill_arg(char **arg, command_ctx_t *ctx, int i, int j)
{
    int start = strcmp(ctx->arg_command[1], "(") == 0;
    int len_array = my_wordarray_len(ctx->arg_command) - 1;
    int last = 0;

    if (i == start + 1 && ctx->arg_command[i][0] == '(') {
        arg[j] = ctx->arg_command[i] + 1;
        last = strlen(arg[j]) - 1;
        arg[j][last] *= (arg[j][last] != ')');
        return;
    }
    if (i == len_array
        && ctx->arg_command[len_array]
        [strlen(ctx->arg_command[len_array]) - 1] == ')') {
        arg[j] = ctx->arg_command[i];
        arg[j][strlen(arg[j]) - 1] = '\0';
        return;
    }
    arg[j] = ctx->arg_command[i];
}

static char **get_array_arg(command_ctx_t *ctx)
{
    int len = get_len_arg(ctx);
    int start = strcmp(ctx->arg_command[1], "(") == 0;
    int j = 0;
    char **arg = malloc(sizeof(char *) * (len + 1));

    if (arg == NULL)
        return NULL;
    arg[len] = NULL;
    arg[0] = ctx->arg_command[0];
    for (int i = start + 1; i < len + start + 1; i++) {
        j = i - start;
        fill_arg(arg, ctx, i, j);
    }
    return arg;
}

static env_t *create_loop_node(char *var, char *new_value)
{
    env_t *node = malloc(sizeof(env_t));

    if (!node) {
        free(new_value);
        return NULL;
    }
    node->key = my_strdup(var);
    if (!node->key) {
        free(new_value);
        free(node);
        return NULL;
    }
    node->value = new_value;
    node->next = NULL;
    return node;
}

static int update_existing_loop_var(env_t *curr, char *arg,
    loop_env_state_t *state)
{
    char *new_value = arg ? my_strdup(arg) : NULL;

    if (arg && !new_value)
        return FAILURE;
    state->existing_node = curr;
    state->saved_value = curr->value;
    curr->value = new_value;
    return SUCCESS;
}

static int set_loop_variable(main_t *main_stock, char *var, char *arg,
    loop_env_state_t *state)
{
    env_t *prev = NULL;
    env_t *curr = find_env_node(main_stock->stock_env, var, &prev);

    state->existing_node = NULL;
    state->created_node = NULL;
    state->saved_value = NULL;
    if (curr)
        return update_existing_loop_var(curr, arg, state);
    state->created_node = create_loop_node(var, arg ? my_strdup(arg) : NULL);
    if (!state->created_node)
        return FAILURE;
    state->created_node->next = main_stock->stock_env;
    main_stock->stock_env = state->created_node;
    return SUCCESS;
}

static void restore_loop_variable(main_t *main_stock, loop_env_state_t *state)
{
    if (state->existing_node) {
        free(state->existing_node->value);
        state->existing_node->value = state->saved_value;
    }
    if (state->created_node) {
        main_stock->stock_env = state->created_node->next;
        free(state->created_node->key);
        free(state->created_node->value);
        free(state->created_node);
    }
}

static int handle_cmd(char **cmd, command_ctx_t *new_ctx,
    handle_arg_t *handle_arg, main_t *main_stock)
{
    loop_env_state_t state = {0};
    int status = SUCCESS;

    status = set_loop_variable(main_stock, handle_arg->var,
        handle_arg->arg, &state);
    if (status == FAILURE)
        return FAILURE;
    for (int j = 0; cmd[j] != NULL; j++) {
        status = parse_command_context(cmd[j], new_ctx, main_stock);
        if (status == 1)
            break;
        if (status == 2)
            continue;
        status = exec_any(main_stock, new_ctx);
        clear_command_ctx(new_ctx);
        if (status == FAILURE)
            break;
    }
    restore_loop_variable(main_stock, &state);
    return status == 1 ? FAILURE : status;
}

static int foreach(command_ctx_t *ctx, char **cmd, main_t *main_stock)
{
    command_ctx_t new_ctx = *ctx;
    handle_arg_t handle_arg = {0};
    char **arg = get_array_arg(ctx);

    if (!arg)
        return FAILURE;
    for (int i = 1; arg[i] != NULL; i++) {
        handle_arg.var = arg[0];
        handle_arg.arg = arg[i];
        if (handle_cmd(cmd, &new_ctx, &handle_arg, main_stock) == FAILURE) {
            free(arg);
            free_array(cmd);
            return 1;
        }
    }
    free(arg);
    free_array(cmd);
    return SUCCESS;
}

int builtin_foreach(main_t *main_stock, command_ctx_t *ctx)
{
    char **cmd = NULL;

    if (handle_error(ctx) == FAILURE)
        return 1;
    cmd = foreach_read_commands();
    if (cmd == NULL)
        return FAILURE;
    return foreach(ctx, cmd, main_stock);
}
