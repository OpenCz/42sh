/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_parsing_env_vars
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

Test(replace_env_vars, returns_null_for_null_args)
{
    main_t stock = {0};

    cr_assert_null(replace_env_vars(NULL, &stock));
}

Test(replace_env_vars, no_dollar_args_unchanged)
{
    main_t stock = {0};
    char **args = my_str_to_word_array("hello world", " ");

    replace_env_vars(args, &stock);
    cr_assert_str_eq(args[0], "hello");
    cr_assert_str_eq(args[1], "world");
    free_array(args);
}

Test(replace_env_vars, replaces_found_env_variable)
{
    env_t node = {.key = "FOO", .value = "bar", .next = NULL};
    main_t stock = {0};
    char **args = malloc(sizeof(char *) * 2);

    stock.stock_env = &node;
    cr_assert_not_null(args);
    args[0] = my_strdup("$FOO");
    args[1] = NULL;
    replace_env_vars(args, &stock);
    cr_assert_str_eq(args[0], "bar");
    free_array(args);
}

Test(replace_env_vars, undefined_var_sets_error_string,
    .init = cr_redirect_stdout)
{
    main_t stock = {0};
    char **args = malloc(sizeof(char *) * 2);

    cr_assert_not_null(args);
    args[0] = my_strdup("$UNDEFINED42SH");
    args[1] = NULL;
    replace_env_vars(args, &stock);
    cr_assert_str_eq(args[0], ": Undefined variable.");
    fflush(stdout);
    cr_assert_stdout_eq_str("UNDEFINED42SH");
    free_array(args);
}

Test(replace_env_vars, hard_coded_dollar_zero)
{
    main_t stock = {0};
    char **args = malloc(sizeof(char *) * 2);

    cr_assert_not_null(args);
    args[0] = my_strdup("$0");
    args[1] = NULL;
    replace_env_vars(args, &stock);
    cr_assert_str_eq(args[0], "c_zsh");
    free_array(args);
}

Test(replace_env_vars, braced_var_syntax)
{
    env_t node = {.key = "BAR", .value = "baz", .next = NULL};
    main_t stock = {0};
    char **args = malloc(sizeof(char *) * 2);

    stock.stock_env = &node;
    cr_assert_not_null(args);
    args[0] = my_strdup("${BAR}");
    args[1] = NULL;
    replace_env_vars(args, &stock);
    cr_assert_str_eq(args[0], "baz");
    free_array(args);
}
