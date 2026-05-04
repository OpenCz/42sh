/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_execution_extra
** Additional execution tests: execute_command chaining, execute_single_command
** edge cases, exec_any with direct paths, alias resolution.
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

static env_t *node_new(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = strdup((char *)key);
    node->value = value ? strdup((char *)value) : NULL;
    node->next = NULL;
    return node;
}
Test(execute_command_extra, empty_string_returns_success)
{
    main_t stock = {0};

    cr_assert_eq(execute_command(&stock, ""), SUCCESS);
}

Test(execute_command_extra, only_whitespace_returns_success)
{
    main_t stock = {0};

    cr_assert_eq(execute_command(&stock, "   "), SUCCESS);
}

Test(execute_command_extra, multiple_semicolons_run_all)
{
    main_t stock = {0};
    env_t *prev = NULL;

    execute_command(&stock, "setenv T1 a; setenv T2 b; setenv T3 c");
    cr_assert_not_null(find_env_node(stock.stock_env, "T1", &prev));
    cr_assert_not_null(find_env_node(stock.stock_env, "T2", &prev));
    cr_assert_not_null(find_env_node(stock.stock_env, "T3", &prev));
    free_linked_list(stock.stock_env);
}

Test(execute_command_extra, last_exit_status_propagated)
{
    main_t stock = {0};
    int ret = execute_command(&stock, "true; false");

    cr_assert_eq(ret, 1);
}

Test(execute_command_extra, builtin_then_external)
{
    main_t stock = {0};
    int ret = execute_command(&stock, "env; true");

    cr_assert_eq(ret, SUCCESS);
}
Test(execute_single_extra, only_tabs_treated_as_blank)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "\t\t", true, false), SUCCESS);
}

Test(execute_single_extra, slash_bin_true_with_path)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "/bin/true", true, false), SUCCESS);
}

Test(execute_single_extra, slash_bin_false_returns_nonzero)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "/bin/false", true, false), 1);
}

Test(execute_single_extra, builtin_setenv_creates_var)
{
    main_t stock = {0};
    env_t *prev = NULL;

    execute_single_command(&stock, "setenv TESTVAR hello", true, false);
    cr_assert_not_null(find_env_node(stock.stock_env, "TESTVAR", &prev));
    free_linked_list(stock.stock_env);
}

Test(execute_single_extra, builtin_disabled_falls_to_external)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "/bin/true", false, false), SUCCESS);
}
Test(exec_any_extra, absolute_path_true_succeeds)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *argv[] = {"/bin/true", NULL};

    stock.stock_env = node_new("PATH", "/bin");
    ctx.command = argv[0];
    ctx.argv = argv;
    cr_assert_eq(exec_any(&stock, &ctx, false), SUCCESS);
    free_linked_list(stock.stock_env);
}

Test(exec_any_extra, absolute_path_false_returns_1)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *argv[] = {"/bin/false", NULL};

    stock.stock_env = node_new("PATH", "/bin");
    ctx.command = argv[0];
    ctx.argv = argv;
    cr_assert_eq(exec_any(&stock, &ctx, false), 1);
    free_linked_list(stock.stock_env);
}

Test(exec_any_extra, command_in_path_resolves_and_runs)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *paths[] = {"/bin", NULL};
    char *argv[] = {"true", NULL};

    stock.path = paths;
    ctx.command = "true";
    ctx.argv = argv;
    cr_assert_eq(exec_any(&stock, &ctx, false), SUCCESS);
}
Test(execute_builtin_extra, setenv_is_registered)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"BKEY", "bval", NULL};

    ctx.command = "setenv";
    ctx.arg_command = args;
    cr_assert_neq(execute_builtin(&stock, &ctx), -1);
    free_linked_list(stock.stock_env);
}

Test(execute_builtin_extra, unsetenv_is_registered)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"BKEY", NULL};

    ctx.command = "unsetenv";
    ctx.arg_command = args;
    cr_assert_neq(execute_builtin(&stock, &ctx), -1);
}

Test(execute_builtin_extra, cd_is_registered)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.command = "cd";
    ctx.arg_command = args;
    cr_assert_neq(execute_builtin(&stock, &ctx), -1);
    free(stock.old_path);
}

Test(execute_builtin_extra, printenv_is_registered)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.command = "printenv";
    ctx.arg_command = args;
    cr_assert_neq(execute_builtin(&stock, &ctx), -1);
}

Test(execute_builtin_extra, repeat_is_registered)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *argv[] = {"repeat", "0", "true", NULL};
    char *args[] = {"0", "true", NULL};

    ctx.command = "repeat";
    ctx.argv = argv;
    ctx.arg_command = args;
    cr_assert_neq(execute_builtin(&stock, &ctx), -1);
}
