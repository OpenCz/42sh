/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_core_init
*/

#include <criterion/criterion.h>
#include "c_zsh.h"

Test(init_env, injects_default_path_when_missing)
{
    char *env[] = {
        "HOME=/home/erwan",
        NULL
    };
    env_t *stock = init_env(env);

    cr_assert_not_null(stock);
    cr_assert_str_eq(stock->key, "PATH");
    cr_assert_str_eq(stock->value, "/bin:/usr/bin");
    cr_assert_not_null(stock->next);
    cr_assert_str_eq(stock->next->key, "HOME");
    cr_assert_str_eq(stock->next->value, "/home/erwan");
    cr_assert_null(stock->next->next);
    free_linked_list(stock);
}

Test(init_env, keeps_existing_path_and_null_values)
{
    char *env[] = {
        "PATH=/custom/bin",
        "FOO",
        NULL
    };
    env_t *stock = init_env(env);

    cr_assert_not_null(stock);
    cr_assert_str_eq(stock->key, "PATH");
    cr_assert_str_eq(stock->value, "/custom/bin");
    cr_assert_not_null(stock->next);
    cr_assert_str_eq(stock->next->key, "FOO");
    cr_assert_null(stock->next->value);
    cr_assert_null(stock->next->next);
    free_linked_list(stock);
}

Test(init_main, initializes_fields_from_env)
{
    char *env[] = {
        "HOME=/home/erwan",
        "PATH=/usr/local/bin:/bin",
        NULL
    };
    main_t *stock = init_main(env);

    cr_assert_not_null(stock);
    cr_assert_not_null(stock->stock_env);
    cr_assert_str_eq(stock->stock_env->key, "HOME");
    cr_assert_str_eq(stock->stock_env->value, "/home/erwan");
    cr_assert_not_null(stock->stock_env->next);
    cr_assert_str_eq(stock->stock_env->next->key, "PATH");
    cr_assert_str_eq(stock->stock_env->next->value, "/usr/local/bin:/bin");
    cr_assert_str_eq(stock->path[0], "/usr/local/bin");
    cr_assert_str_eq(stock->path[1], "/bin");
    cr_assert_null(stock->path[2]);
    cr_assert_str_eq(stock->home, "/home/erwan");
    cr_assert_null(stock->command);
    cr_assert_null(stock->argv);
    cr_assert_null(stock->arg_command);
    cr_assert_null(stock->redirection);
    cr_assert_null(stock->old_path);
    free_main(stock);
}

