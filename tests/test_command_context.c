/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_command_context
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(command_context, parse_empty_command_returns_2)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    cr_assert_eq(parse_command_context("", &ctx, &stock), 2);
}

Test(command_context, parse_command_sets_fields_and_redirection)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    cr_assert_eq(parse_command_context("echo hello > out.txt", &ctx, &stock), SUCCESS);
    cr_assert_str_eq(ctx.command, "echo");
    cr_assert_str_eq(ctx.argv[0], "echo");
    cr_assert_str_eq(ctx.argv[1], "hello");
    cr_assert_str_eq(ctx.redirection, ">");
    clear_command_ctx(&ctx);
}

Test(command_context, bind_transfers_ownership_to_main)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};

    stock.argv = my_str_to_word_array("old value", " ");
    stock.redirection = my_strdup("<");
    cr_assert_eq(parse_command_context("ls -l", &ctx, &stock), SUCCESS);
    cr_assert_eq(bind_command_context(&stock, &ctx), SUCCESS);
    cr_assert_null(ctx.argv);
    cr_assert_null(ctx.redirection);
    cr_assert_str_eq(stock.command, "ls");
    cr_assert_str_eq(stock.argv[1], "-l");
    free_array(stock.argv);
    free(stock.redirection);
}

