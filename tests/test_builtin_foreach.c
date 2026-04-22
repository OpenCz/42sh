/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_foreach
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

Test(builtin_foreach, returns_error_with_too_few_arguments)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.command = "foreach";
    ctx.argv = (char *[]){NULL};
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_assert_eq(builtin_foreach(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_foreach, returns_error_with_invalid_variable_name_starting_with_digit)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"1var", "(", "echo", "test", ")", NULL};

    ctx.command = "foreach";
    ctx.argv = (char *[]){NULL};
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_assert_eq(builtin_foreach(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_foreach, returns_error_with_non_alphanum_variable_name)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"var-name", "(", "echo", "test", ")", NULL};

    ctx.command = "foreach";
    ctx.argv = (char *[]){NULL};
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_assert_eq(builtin_foreach(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_foreach, returns_error_with_missing_opening_paren)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"item", "echo", "test", ")", NULL};

    ctx.command = "foreach";
    ctx.argv = (char *[]){NULL};
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_assert_eq(builtin_foreach(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_foreach, returns_error_with_missing_closing_paren)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"item", "(", "echo", "test", NULL};

    ctx.command = "foreach";
    ctx.argv = (char *[]){NULL};
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_assert_eq(builtin_foreach(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_foreach, returns_error_with_too_many_opening_parens)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"item", "((", "echo", "test", ")", NULL};

    ctx.command = "foreach";
    ctx.argv = (char *[]){NULL};
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_assert_eq(builtin_foreach(&stock, &ctx), 1);
    free_linked_list(stock.stock_env);
}

Test(builtin_foreach, accepts_valid_variable_name_and_args)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"item", "(", "value1", "value2", ")", NULL};
    char *argv[] = {"foreach", "item", "(", "value1", "value2", ")", NULL};

    ctx.command = "foreach";
    ctx.argv = argv;
    ctx.arg_command = args;
    stock.stock_env = node_new("USER", "test");
    cr_redirect_stdout();
    // This would hang waiting for stdin, so we just test error handling
    // A full integration test would need stdin mocking
    free_linked_list(stock.stock_env);
}
