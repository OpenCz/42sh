/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_execution_operator
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

TestSuite(execute_operator, .init = redirect_all);

Test(execute_operator, and_runs_second_when_first_succeeds)
{
    main_t stock = {0};
    env_t *prev = NULL;

    execute_operator(&stock, "env&&setenv ANDVAR1 passed");
    cr_assert_not_null(find_env_node(stock.stock_env, "ANDVAR1", &prev));
    free_linked_list(stock.stock_env);
}

Test(execute_operator, and_skips_second_when_first_fails)
{
    main_t stock = {0};
    env_t *prev = NULL;

    execute_operator(&stock, "cd /nonexistent42sh&&setenv SKIPVAR1 set");
    cr_assert_null(find_env_node(stock.stock_env, "SKIPVAR1", &prev));
}

Test(execute_operator, or_short_circuits_when_first_succeeds)
{
    main_t stock = {0};
    env_t *prev = NULL;

    execute_operator(&stock, "env||setenv ORSKIP1 set");
    cr_assert_null(find_env_node(stock.stock_env, "ORSKIP1", &prev));
}

Test(execute_operator, or_runs_second_when_first_fails)
{
    main_t stock = {0};
    env_t *prev = NULL;

    execute_operator(&stock, "cd /nonexistent42sh||setenv ORVAR1 passed");
    cr_assert_not_null(find_env_node(stock.stock_env, "ORVAR1", &prev));
    free_linked_list(stock.stock_env);
}

Test(execute_operator, returns_error_on_empty_command)
{
    main_t stock = {0};

    cr_assert_eq(execute_operator(&stock, ""), 1);
}
