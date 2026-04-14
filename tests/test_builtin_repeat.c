/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_repeat
*/

#include <criterion/criterion.h>
#include "42sh.h"

Test(builtin_repeat, zero_count_returns_success_without_mutating_ctx)
{
    command_ctx_t ctx = {0};
    main_t stock = {0};
    char **argv = my_str_to_word_array("repeat 0 /bin/true", " ");

    cr_assert_not_null(argv);
    ctx.command = argv[0];
    ctx.argv = argv;
    ctx.arg_command = &argv[1];
    cr_assert_eq(builtin_repeat(&stock, &ctx), SUCCESS);
    cr_assert_eq(ctx.argv, argv);
    cr_assert_str_eq(ctx.command, "repeat");
    free_array(argv);
}

Test(builtin_repeat, executes_direct_command_and_returns_child_status)
{
    command_ctx_t ctx = {0};
    main_t stock = {0};
    char *args[] = {"2", "true", NULL};
    char *argv[] = {"repeat", "2", "true", NULL};

    ctx.command = argv[0];
    ctx.argv = argv;
    ctx.arg_command = args;
    cr_assert_eq(builtin_repeat(&stock, &ctx), SUCCESS);
}

