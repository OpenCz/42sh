/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_foreach
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"
Test(handle_error, too_few_args_zero_elements, .init = cr_redirect_stdout)
{
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), FAILURE);
}

Test(handle_error, too_few_args_one_element, .init = cr_redirect_stdout)
{
    command_ctx_t ctx = {0};
    char *args[] = {"i", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), FAILURE);
}

Test(handle_error, var_name_starts_with_digit, .init = cr_redirect_stdout)
{
    command_ctx_t ctx = {0};
    char *args[] = {"1var", "(a)", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), FAILURE);
}

Test(handle_error, var_name_not_alphanum, .init = cr_redirect_stdout)
{
    command_ctx_t ctx = {0};
    char *args[] = {"var_1", "(a)", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), FAILURE);
}

Test(handle_error, words_not_parenthesized, .init = cr_redirect_stdout)
{
    command_ctx_t ctx = {0};
    char *args[] = {"i", "a", "b", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), FAILURE);
}

Test(handle_error, missing_closing_paren, .init = cr_redirect_stdout)
{
    command_ctx_t ctx = {0};
    char *args[] = {"i", "(a", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), FAILURE);
}

Test(handle_error, valid_compact_parentheses)
{
    command_ctx_t ctx = {0};
    char *args[] = {"i", "(a)", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), SUCCESS);
}

Test(handle_error, valid_separate_parentheses)
{
    command_ctx_t ctx = {0};
    char *args[] = {"i", "(", "a", "b)", NULL};

    ctx.arg_command = args;
    cr_assert_eq(handle_error(&ctx), SUCCESS);
}
