/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_setenv
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
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

Test(builtin_setenv, inserts_new_variable)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"EDITOR", "vim", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_key(stock.stock_env, "EDITOR"));
    cr_assert_str_eq(find_key(stock.stock_env, "EDITOR")->value, "vim");
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, updates_existing_variable)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"USER", "root", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), SUCCESS);
    cr_assert_str_eq(find_key(stock.stock_env, "USER")->value, "root");
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, rejects_name_starting_with_digit)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"1BAD", "x", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), 1);
    cr_assert_null(find_key(stock.stock_env, "1BAD"));
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, rejects_too_many_arguments)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"A", "B", "C", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(my_setenv, wrapper_inserts_variable)
{
    main_t stock = {0};
    char *args[] = {"EDITOR", "nvim", NULL};

    stock.stock_env = node_new("USER", "erwan");
    stock.arg_command = args;
    cr_assert_eq(my_setenv(&stock), SUCCESS);
    cr_assert_str_eq(find_key(stock.stock_env, "EDITOR")->value, "nvim");
    free_linked_list(stock.stock_env);
}

Test(my_setenv, wrapper_without_key_prints_environment)
{
    main_t stock = {0};
    char *args[] = {NULL};

    stock.stock_env = node_new("HOME", "/home/erwan");
    stock.arg_command = args;
    cr_redirect_stdout();
    cr_assert_eq(my_setenv(&stock), SUCCESS);
    fflush(stdout);
    cr_assert_stdout_eq_str("HOME=/home/erwan\n");
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, inserts_into_empty_environment)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"SHELL", "/bin/42sh", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_key(stock.stock_env, "SHELL"));
    cr_assert_str_eq(find_key(stock.stock_env, "SHELL")->value, "/bin/42sh");
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, appends_after_last_node)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"EDITOR", "nano", NULL};
    env_t *head = node_new("USER", "erwan");

    head->next = node_new("PATH", "/bin");
    stock.stock_env = head;
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_key(stock.stock_env, "EDITOR"));
    cr_assert_str_eq(find_key(stock.stock_env, "EDITOR")->value, "nano");
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, missing_value_sets_empty_string)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"EMPTY", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_key(stock.stock_env, "EMPTY"));
    cr_assert_str_eq(find_key(stock.stock_env, "EMPTY")->value, "");
    free_linked_list(stock.stock_env);
}

Test(builtin_setenv, rejects_non_alphanumeric_name)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"BAD-NAME", "x", NULL};

    stock.stock_env = node_new("USER", "erwan");
    ctx.arg_command = args;
    cr_assert_eq(builtin_setenv(&stock, &ctx), 1);
    cr_assert_null(find_key(stock.stock_env, "BAD-NAME"));
    free_linked_list(stock.stock_env);
}
