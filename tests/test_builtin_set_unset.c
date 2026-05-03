/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_set_unset
** Covers: builtin_set, builtin_unset (local variable management)
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

static env_t *find_local(env_t *env, const char *key)
{
    for (; env; env = env->next)
        if (my_strcmp(env->key, (char *)key) == 0)
            return env;
    return NULL;
}
Test(builtin_set, no_args_returns_success)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_null(stock.stock_local_var);
}

Test(builtin_set, inline_assignment_sets_key_and_value)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"FOO=bar", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "FOO"));
    cr_assert_str_eq(find_local(stock.stock_local_var, "FOO")->value, "bar");
    free_linked_list(stock.stock_local_var);
}

Test(builtin_set, separate_args_sets_key_and_value)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"BAR", "=", "baz", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "BAR"));
    cr_assert_str_eq(find_local(stock.stock_local_var, "BAR")->value, "baz");
    free_linked_list(stock.stock_local_var);
}

Test(builtin_set, no_equals_pushes_empty_value)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"NOVALUE", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "NOVALUE"));
    cr_assert_str_eq(find_local(stock.stock_local_var, "NOVALUE")->value, "");
    free_linked_list(stock.stock_local_var);
}

Test(builtin_set, updates_existing_local_var)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args1[] = {"X=first", NULL};
    char *args2[] = {"X=second", NULL};

    ctx.arg_command = args1;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    ctx.arg_command = args2;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_str_eq(find_local(stock.stock_local_var, "X")->value, "second");
    free_linked_list(stock.stock_local_var);
}

Test(builtin_set, multiple_inline_vars_are_all_stored)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args1[] = {"A=1", NULL};
    char *args2[] = {"B=2", NULL};

    ctx.arg_command = args1;
    builtin_set(&stock, &ctx);
    ctx.arg_command = args2;
    builtin_set(&stock, &ctx);
    cr_assert_not_null(find_local(stock.stock_local_var, "A"));
    cr_assert_not_null(find_local(stock.stock_local_var, "B"));
    cr_assert_str_eq(find_local(stock.stock_local_var, "A")->value, "1");
    cr_assert_str_eq(find_local(stock.stock_local_var, "B")->value, "2");
    free_linked_list(stock.stock_local_var);
}

Test(builtin_set, inline_assignment_with_empty_value)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"EMPTY=", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "EMPTY"));
    free_linked_list(stock.stock_local_var);
}

Test(builtin_set, two_args_without_value_uses_empty)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"KEY", "=", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_set(&stock, &ctx), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "KEY"));
    cr_assert_str_eq(find_local(stock.stock_local_var, "KEY")->value, "");
    free_linked_list(stock.stock_local_var);
}
Test(builtin_unset, null_key_returns_error)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_unset(&stock, &ctx), 1);
}

Test(builtin_unset, removes_existing_head_node)
{
    main_t stock = {0};
    command_ctx_t ctx_set = {0};
    command_ctx_t ctx_unset = {0};
    char *set_args[] = {"MYVAR=hello", NULL};
    char *unset_args[] = {"MYVAR", NULL};

    ctx_set.arg_command = set_args;
    builtin_set(&stock, &ctx_set);
    cr_assert_not_null(find_local(stock.stock_local_var, "MYVAR"));
    ctx_unset.arg_command = unset_args;
    cr_assert_eq(builtin_unset(&stock, &ctx_unset), SUCCESS);
    cr_assert_null(find_local(stock.stock_local_var, "MYVAR"));
}

Test(builtin_unset, not_found_returns_success)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"DOES_NOT_EXIST", NULL};

    ctx.arg_command = args;
    cr_assert_eq(builtin_unset(&stock, &ctx), SUCCESS);
}

Test(builtin_unset, removes_non_head_node)
{
    main_t stock = {0};
    command_ctx_t ctx_set = {0};
    command_ctx_t ctx_unset = {0};
    char *set1[] = {"A=1", NULL};
    char *set2[] = {"B=2", NULL};
    char *set3[] = {"C=3", NULL};
    char *unset_args[] = {"B", NULL};

    ctx_set.arg_command = set1;
    builtin_set(&stock, &ctx_set);
    ctx_set.arg_command = set2;
    builtin_set(&stock, &ctx_set);
    ctx_set.arg_command = set3;
    builtin_set(&stock, &ctx_set);
    ctx_unset.arg_command = unset_args;
    cr_assert_eq(builtin_unset(&stock, &ctx_unset), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "A"));
    cr_assert_null(find_local(stock.stock_local_var, "B"));
    cr_assert_not_null(find_local(stock.stock_local_var, "C"));
    free_linked_list(stock.stock_local_var);
}

Test(builtin_unset, removes_tail_node)
{
    main_t stock = {0};
    command_ctx_t ctx_set = {0};
    command_ctx_t ctx_unset = {0};
    char *set1[] = {"X=1", NULL};
    char *set2[] = {"Y=2", NULL};
    char *unset_args[] = {"Y", NULL};

    ctx_set.arg_command = set1;
    builtin_set(&stock, &ctx_set);
    ctx_set.arg_command = set2;
    builtin_set(&stock, &ctx_set);
    ctx_unset.arg_command = unset_args;
    cr_assert_eq(builtin_unset(&stock, &ctx_unset), SUCCESS);
    cr_assert_not_null(find_local(stock.stock_local_var, "X"));
    cr_assert_null(find_local(stock.stock_local_var, "Y"));
    free_linked_list(stock.stock_local_var);
}

Test(builtin_unset, double_unset_second_is_noop)
{
    main_t stock = {0};
    command_ctx_t ctx_set = {0};
    command_ctx_t ctx_unset = {0};
    char *set_args[] = {"Z=42", NULL};
    char *unset_args[] = {"Z", NULL};

    ctx_set.arg_command = set_args;
    builtin_set(&stock, &ctx_set);
    ctx_unset.arg_command = unset_args;
    builtin_unset(&stock, &ctx_unset);
    cr_assert_eq(builtin_unset(&stock, &ctx_unset), SUCCESS);
    cr_assert_null(find_local(stock.stock_local_var, "Z"));
}
