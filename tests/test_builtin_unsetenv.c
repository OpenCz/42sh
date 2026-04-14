/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_unsetenv
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

static env_t *node_new(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = my_strdup((char *)key);
    node->value = value ? my_strdup((char *)value) : NULL;
    node->next = NULL;
    return node;
}

static env_t *find_key(env_t *env, const char *key)
{
    for (; env; env = env->next)
        if (my_strcmp(env->key, (char *)key) == 0)
            return env;
    return NULL;
}

Test(builtin_unsetenv, removes_existing_variable)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"USER", NULL};
    env_t *user = node_new("USER", "erwan");
    env_t *path = node_new("PATH", "/bin");

    user->next = path;
    stock.stock_env = user;
    ctx.arg_command = args;
    cr_assert_eq(builtin_unsetenv(&stock, &ctx), SUCCESS);
    cr_assert_null(find_key(stock.stock_env, "USER"));
    cr_assert_not_null(find_key(stock.stock_env, "PATH"));
    free_linked_list(stock.stock_env);
}

Test(builtin_unsetenv, unknown_variable_is_noop)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"DOES_NOT_EXIST", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_unsetenv(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_key(stock.stock_env, "USER"));
    free_linked_list(stock.stock_env);
}

Test(builtin_unsetenv, missing_argument_returns_error)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_unsetenv(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_unsetenv, removes_non_head_variable)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"PATH", NULL};
    env_t *head = node_new("USER", "erwan");

    head->next = node_new("PATH", "/bin");
    head->next->next = node_new("HOME", "/home/erwan");
    stock.stock_env = head;
    ctx.arg_command = args;
    cr_assert_eq(builtin_unsetenv(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_key(stock.stock_env, "USER"));
    cr_assert_null(find_key(stock.stock_env, "PATH"));
    cr_assert_not_null(find_key(stock.stock_env, "HOME"));
    free_linked_list(stock.stock_env);
}

Test(my_unsetenv, wrapper_removes_variable)
{
    main_t stock = {0};
    char *args[] = {"USER", NULL};

    stock.stock_env = node_new("USER", "erwan");
    stock.arg_command = args;
    cr_assert_eq(my_unsetenv(&stock), SUCCESS);
    cr_assert_null(find_key(stock.stock_env, "USER"));
    free_linked_list(stock.stock_env);
}
