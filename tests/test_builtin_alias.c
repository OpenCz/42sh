/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_alias
** Covers: builtin_alias
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

static alias_stock_t *find_alias(alias_stock_t *head, const char *name)
{
    for (; head; head = head->next)
        if (my_strcmp(head->new_name, (char *)name) == 0)
            return head;
    return NULL;
}

static void free_aliases(alias_stock_t *head)
{
    alias_stock_t *next;

    while (head) {
        next = head->next;
        free(head->new_name);
        free(head->command);
        free(head);
        head = next;
    }
}
Test(builtin_alias, registers_simple_alias)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"ll=ls -la", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_alias(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_alias(stock.alias_stock, "ll"));
    cr_assert_str_eq(find_alias(stock.alias_stock, "ll")->command, "ls -la");
    free_aliases(stock.alias_stock);
}

Test(builtin_alias, registers_second_alias_at_head)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args1[] = {"a=echo hello", NULL};
    char *args2[] = {"b=cat /etc/passwd", NULL};

    ctx.arg_command = args1;
    builtin_alias(&stock, &ctx);
    ctx.arg_command = args2;
    cr_assert_eq(builtin_alias(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_alias(stock.alias_stock, "a"));
    cr_assert_not_null(find_alias(stock.alias_stock, "b"));
    free_aliases(stock.alias_stock);
}

Test(builtin_alias, null_arg_returns_error)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_alias(&stock, &ctx), 1);
    cr_assert_null(stock.alias_stock);
}

Test(builtin_alias, no_equals_sign_returns_error)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"noequalssign", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_alias(&stock, &ctx), 1);
    cr_assert_null(stock.alias_stock);
}

Test(builtin_alias, alias_is_not_fixed_by_default)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"myalias=mycommand", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_alias(&stock, &ctx), SUCCESS);
    cr_assert_not_null(stock.alias_stock);
    cr_assert_eq(stock.alias_stock->is_fixed, false);
    free_aliases(stock.alias_stock);
}

Test(builtin_alias, stores_name_and_command_separately)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"greet=echo hello world", NULL};

    ctx.arg_command = args;
    builtin_alias(&stock, &ctx);
    cr_assert_str_eq(stock.alias_stock->new_name, "greet");
    cr_assert_str_eq(stock.alias_stock->command, "echo hello world");
    free_aliases(stock.alias_stock);
}

Test(builtin_alias, new_alias_placed_at_head_of_list)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args1[] = {"first=cmd1", NULL};
    char *args2[] = {"second=cmd2", NULL};

    ctx.arg_command = args1;
    builtin_alias(&stock, &ctx);
    ctx.arg_command = args2;
    builtin_alias(&stock, &ctx);
    cr_assert_str_eq(stock.alias_stock->new_name, "second");
    free_aliases(stock.alias_stock);
}
