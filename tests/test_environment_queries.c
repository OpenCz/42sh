/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_environment_queries
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/c_zsh.h"

static env_t *node_new(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = strdup((char *)key);
    node->value = value ? strduphar *)value) : NULL;
    node->next = NULL;
    return node;
}

Test(get_home, returns_null_when_missing)
{
    env_t *head = node_new("PATH", "/bin");

    cr_assert_null(get_home(head));
    free_linked_list(head);
}

Test(get_home, returns_home_when_present)
{
    env_t *head = node_new("HOME", "/home/erwan");

    cr_assert_str_eq(get_home(head), "/home/erwan");
    free_linked_list(head);
}

Test(get_path, returns_null_when_missing)
{
    env_t *head = node_new("HOME", "/home/erwan");

    cr_assert_null(get_path(head));
    free_linked_list(head);
}

Test(get_path, returns_path_when_present)
{
    env_t *head = node_new("PATH", "/bin:/usr/bin");

    cr_assert_str_eq(get_path(head), "/bin:/usr/bin");
    free_linked_list(head);
}

Test(check_bin, returns_full_path_for_existing_executable)
{
    cr_assert_str_eq(check_bin("true", "/bin"), "/bin/true");
}

Test(check_bin, returns_null_for_missing_directory)
{
    cr_assert_null(check_bin("true", "/this/path/does/not/exist"));
}

Test(check_bin, returns_null_for_directory_command)
{
    cr_redirect_stderr();
    cr_assert_null(check_bin("/tmp", "/bin"));
}

Test(check_bin, returns_null_when_command_is_null)
{
    cr_assert_null(check_bin(NULL, "/bin"));
}

Test(check_bin, returns_null_when_path_is_null)
{
    cr_assert_null(check_bin("true", NULL));
}

Test(loop_bin, uses_default_path_array_when_missing)
{
    main_t stock = {0};
    char *path = loop_bin(&stock, "true");

    cr_assert_not_null(path);
    cr_assert_str_eq(path, "/bin/true");
    free(path);
    free_array(stock.path);
}

Test(loop_bin, returns_null_when_stock_is_null)
{
    cr_assert_null(loop_bin(NULL, "true"));
}

Test(loop_bin, returns_null_when_command_is_not_found)
{
    main_t stock = {0};
    char *paths[] = {"/bin", NULL};

    stock.path = paths;
    cr_assert_null(loop_bin(&stock, "__definitely_missing_42sh_binary__"));
}

Test(get_user, returns_null_when_user_missing)
{
    env_t *head = node_new("HOME", "/home/erwan");

    cr_assert_null(get_user(head));
    free_linked_list(head);
}

Test(get_user, returns_user_when_present)
{
    env_t *head = node_new("USER", "erwan");

    cr_assert_str_eq(get_user(head), "erwan");
    free_linked_list(head);
}

Test(get_user, finds_user_among_multiple_nodes)
{
    env_t *n1 = node_new("HOME", "/home/erwan");
    env_t *n2 = node_new("USER", "sacha");

    n1->next = n2;
    cr_assert_str_eq(get_user(n1), "sacha");
    free_linked_list(n1);
}
