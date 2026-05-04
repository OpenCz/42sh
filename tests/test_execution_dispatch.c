/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_execution_dispatch
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(execute_builtin, resolves_known_and_unknown_commands)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    ctx.command = "env";
    cr_assert_eq(execute_builtin(&stock, &ctx), SUCCESS);
    ctx.command = "not_a_builtin";
    cr_assert_eq(execute_builtin(&stock, &ctx), -1);
}

Test(execute_single_command, returns_error_on_null_command)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, NULL, true), 1);
}

Test(execute_single_command, skips_blank_command)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "   ", true), SUCCESS);
}

Test(execute_single_command, runs_builtin_when_allowed)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "env", true), SUCCESS);
}

Test(execute_single_command, falls_back_to_external_command)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "true", true), SUCCESS);
}

Test(execute_single_command, runs_external_when_builtins_are_disabled)
{
    main_t stock = {0};

    cr_assert_eq(execute_single_command(&stock, "true", false), SUCCESS);
}

Test(execute_command, returns_status_of_last_semicolon_command)
{
    main_t stock = {0};

    cr_assert_eq(execute_command(&stock, "true; nope_does_not_exist"), 1);
}

Test(execute_command, routes_pipe_commands_to_pipeline)
{
    main_t stock = {0};

    cr_assert_eq(execute_command(&stock, "true | cat"), SUCCESS);
}

Test(execute_command, rejects_null_command)
{
    main_t stock = {0};

    cr_assert_eq(execute_command(&stock, NULL), 1);
}

