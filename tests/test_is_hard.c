/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_is_hard
** Covers: is_hard (special variable resolution: $0, $?, $$, easter eggs)
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

static void init_hard_stock(main_t *stock)
{
    static job_controler_t controler = {0};

    stock->controler = &controler;
}

Test(is_hard, dollar_zero_returns_shell_name)
{
    main_t stock = {0};

    init_hard_stock(&stock);
    char *result = is_hard("0", 1, &stock);

    cr_assert_not_null(result);
    cr_assert_str_eq(result, "c_zsh");
}

Test(is_hard, dollar_question_mark_returns_last_exit)
{
    main_t stock = {0};
    char *result;

    init_hard_stock(&stock);
    stock.last_exit = "42";
    result = is_hard("?", 1, &stock);
    cr_assert_not_null(result);
    cr_assert_str_eq(result, "42");
}

Test(is_hard, dollar_question_mark_null_last_exit)
{
    main_t stock = {0};
    char *result;

    init_hard_stock(&stock);
    stock.last_exit = NULL;
    result = is_hard("?", 1, &stock);
    cr_assert_null(result);
}

Test(is_hard, dollar_dollar_returns_pid_string)
{
    main_t stock = {0};
    init_hard_stock(&stock);
    char *result = is_hard("$", 1, &stock);
    char *expected = my_itoa((int)getpid());

    cr_assert_not_null(result);
    cr_assert_not_null(expected);
    cr_assert_str_eq(result, expected);
    free(expected);
    free(result);
}

Test(is_hard, unknown_key_returns_null)
{
    main_t stock = {0};

    init_hard_stock(&stock);

    cr_assert_null(is_hard("UNKNOWN_XYZZY", 13, &stock));
}

Test(is_hard, empty_key_returns_null)
{
    main_t stock = {0};

    init_hard_stock(&stock);

    cr_assert_null(is_hard("", 0, &stock));
}

Test(is_hard, key_length_must_match_exactly)
{
    main_t stock = {0};

    init_hard_stock(&stock);

    cr_assert_null(is_hard("0extra", 6, &stock));
}

Test(is_hard, easter_egg_36_is_accessible)
{
    main_t stock = {0};
    init_hard_stock(&stock);
    char *result = is_hard("36", 2, &stock);

    cr_assert_not_null(result);
}

Test(is_hard, easter_egg_69_is_accessible)
{
    main_t stock = {0};
    init_hard_stock(&stock);
    char *result = is_hard("69", 2, &stock);

    cr_assert_not_null(result);
}
