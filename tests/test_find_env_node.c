/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_find_env_node
** Covers: find_env_node
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

static env_t *node_new(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = strdup((char *)key);
    node->value = value ? strdup((char *)value) : NULL;
    node->next = NULL;
    return node;
}
Test(find_env_node, returns_null_for_null_env)
{
    env_t *prev = NULL;

    cr_assert_null(find_env_node(NULL, "KEY", &prev));
    cr_assert_null(prev);
}

Test(find_env_node, finds_single_head_node)
{
    env_t *head = node_new("HOME", "/home/erwan");
    env_t *prev = NULL;
    env_t *found = find_env_node(head, "HOME", &prev);

    cr_assert_not_null(found);
    cr_assert_str_eq(found->key, "HOME");
    cr_assert_null(prev);
    free_linked_list(head);
}

Test(find_env_node, finds_tail_and_sets_prev)
{
    env_t *n1 = node_new("A", "1");
    env_t *n2 = node_new("B", "2");
    env_t *prev = NULL;
    env_t *found;

    n1->next = n2;
    found = find_env_node(n1, "B", &prev);
    cr_assert_not_null(found);
    cr_assert_str_eq(found->key, "B");
    cr_assert_eq(prev, n1);
    free_linked_list(n1);
}

Test(find_env_node, finds_middle_node)
{
    env_t *n1 = node_new("A", "1");
    env_t *n2 = node_new("B", "2");
    env_t *n3 = node_new("C", "3");
    env_t *prev = NULL;
    env_t *found;

    n1->next = n2;
    n2->next = n3;
    found = find_env_node(n1, "B", &prev);
    cr_assert_not_null(found);
    cr_assert_str_eq(found->key, "B");
    cr_assert_eq(prev, n1);
    free_linked_list(n1);
}

Test(find_env_node, returns_null_when_key_not_found)
{
    env_t *head = node_new("HOME", "/home/erwan");
    env_t *prev = NULL;

    cr_assert_null(find_env_node(head, "MISSING", &prev));
    free_linked_list(head);
}

Test(find_env_node, returns_null_and_prev_null_on_miss_single)
{
    env_t *head = node_new("X", "1");
    env_t *prev = NULL;

    cr_assert_null(find_env_node(head, "NOTHERE", &prev));
    free_linked_list(head);
}

Test(find_env_node, finds_in_three_node_list_at_head)
{
    env_t *n1 = node_new("FIRST", "a");
    env_t *n2 = node_new("SECOND", "b");
    env_t *n3 = node_new("THIRD", "c");
    env_t *prev = NULL;
    env_t *found;

    n1->next = n2;
    n2->next = n3;
    found = find_env_node(n1, "FIRST", &prev);
    cr_assert_not_null(found);
    cr_assert_str_eq(found->key, "FIRST");
    cr_assert_null(prev);
    free_linked_list(n1);
}

Test(find_env_node, value_accessible_on_found_node)
{
    env_t *head = node_new("PATH", "/bin:/usr/bin");
    env_t *prev = NULL;
    env_t *found = find_env_node(head, "PATH", &prev);

    cr_assert_not_null(found);
    cr_assert_str_eq(found->value, "/bin:/usr/bin");
    free_linked_list(head);
}

Test(find_env_node, case_sensitive_search)
{
    env_t *head = node_new("home", "/home/erwan");
    env_t *prev = NULL;

    cr_assert_null(find_env_node(head, "HOME", &prev));
    cr_assert_not_null(find_env_node(head, "home", &prev));
    free_linked_list(head);
}
