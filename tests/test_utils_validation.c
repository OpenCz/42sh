/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_utils_validation
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(my_char_isnum, validates_first_character)
{
    cr_assert_eq(my_char_isnum("1abc"), 1);
    cr_assert_eq(my_char_isnum("abc"), 0);
}

Test(my_str_is_alphanum, validates_alphanumeric_only)
{
    cr_assert_eq(my_str_is_alphanum("A1b2C3"), 0);
    cr_assert_eq(my_str_is_alphanum("A_B"), 1);
}

Test(my_char_is_alpha, returns_success_for_letters)
{
    cr_assert_eq(my_char_is_alpha('a'), SUCCESS);
    cr_assert_eq(my_char_is_alpha('z'), SUCCESS);
    cr_assert_eq(my_char_is_alpha('A'), SUCCESS);
    cr_assert_eq(my_char_is_alpha('Z'), SUCCESS);
}

Test(my_char_is_alpha, returns_error_for_non_letters)
{
    cr_assert_eq(my_char_is_alpha('0'), 1);
    cr_assert_eq(my_char_is_alpha('_'), 1);
    cr_assert_eq(my_char_is_alpha(' '), 1);
    cr_assert_eq(my_char_is_alpha('!'), 1);
}

