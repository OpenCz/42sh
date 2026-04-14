/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_builtin_env
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "c_zsh.h"

static void redirect_all(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static env_t *node_new(const char *key, const char *value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = my_strdup((char *)key);
    node->value = value ? my_strdup((char *)value) : NULL;
    node->next = NULL;
    return node;
}

static void node_free_all(env_t *head)
{
    free_linked_list(head);
}

TestSuite(builtin_env, .init = redirect_all);

Test(builtin_env, prints_each_variable_with_newline)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    env_t *n1 = node_new("USER", "erwan");
    env_t *n2 = node_new("EMPTY", NULL);

    n1->next = n2;
    stock.stock_env = n1;
    cr_assert_eq(builtin_env(&stock, &ctx), SUCCESS);
    fflush(stdout);
    cr_assert_stdout_eq_str("USER=erwan\nEMPTY=\n");
    node_free_all(n1);
}

