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

