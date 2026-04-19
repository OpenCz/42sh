/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_exec_any
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

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

Test(exec_any, direct_path_that_does_not_exist_returns_error)
{
    main_t stock = {0};
    command_ctx_t ctx = {0};
    char *args[] = {"/tmp/42sh_exec_any_missing", NULL};

    stock.stock_env = node_new("PATH", "/bin");
    ctx.command = args[0];
    ctx.argv = args;
    cr_assert_eq(exec_any(&stock, &ctx), 1);
    node_free_all(stock.stock_env);
}

