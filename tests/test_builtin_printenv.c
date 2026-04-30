/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_printenv
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

static env_t *make_node(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = my_strdup((char *)key);
    node->value = value ? my_strdup((char *)value) : NULL;
    node->next = NULL;
    return node;
}

Test(builtin_printenv, no_args_prints_all_env, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    env_t *node = make_node("MYVAR", "42");
    char *args[] = {NULL};

    stock.stock_env = node;
    ctx.arg_command = args;
    cr_assert_eq(builtin_printenv(&stock, &ctx), SUCCESS);
    fflush(stdout);
    cr_assert_stdout_eq_str("MYVAR=42\n");
    free_linked_list(node);
}

Test(builtin_printenv, one_arg_found_prints_value, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    env_t *node = make_node("HOME", "/home/user");
    char *args[] = {"HOME", NULL};

    stock.stock_env = node;
    ctx.arg_command = args;
    cr_assert_eq(builtin_printenv(&stock, &ctx), SUCCESS);
    fflush(stdout);
    cr_assert_stdout_eq_str("/home/user\n");
    free_linked_list(node);
}

Test(builtin_printenv, one_arg_not_found_returns_error)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"NOTHERE", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_printenv(&stock, &ctx), 1);
}

Test(builtin_printenv, too_many_args_returns_error, .init = cr_redirect_stderr)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"A", "B", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_printenv(&stock, &ctx), 1);
    fflush(stderr);
    cr_assert_stderr_eq_str("printenv: Too many arguments.\n");
}

Test(builtin_printenv, finds_variable_among_several, .init = cr_redirect_stdout)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    env_t *n1 = make_node("PATH", "/bin");
    env_t *n2 = make_node("USER", "erwan");
    char *args[] = {"USER", NULL};

    n1->next = n2;
    stock.stock_env = n1;
    ctx.arg_command = args;
    cr_assert_eq(builtin_printenv(&stock, &ctx), SUCCESS);
    fflush(stdout);
    cr_assert_stdout_eq_str("erwan\n");
    free_linked_list(n1);
}
