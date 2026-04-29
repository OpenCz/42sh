/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** test_memory
*/

#include <criterion/criterion.h>
#include "../include/c_zsh.h"

Test(free_alloc, handles_null_pointer)
{
    free_alloc(NULL);
}

Test(free_alloc, frees_valid_heap_block)
{
    void *ptr = malloc(32);

    cr_assert_not_null(ptr);
    free_alloc(ptr);
}

Test(free_linked_list, handles_null_list)
{
    free_linked_list(NULL);
}

Test(free_linked_list, frees_single_node)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = my_strdup("KEY");
    node->value = my_strdup("VAL");
    node->next = NULL;
    free_linked_list(node);
}

Test(free_linked_list, frees_node_with_null_value)
{
    env_t *node = malloc(sizeof(env_t));

    cr_assert_not_null(node);
    node->key = my_strdup("NOVAL");
    node->value = NULL;
    node->next = NULL;
    free_linked_list(node);
}

Test(free_linked_list, frees_multiple_nodes)
{
    env_t *n1 = malloc(sizeof(env_t));
    env_t *n2 = malloc(sizeof(env_t));

    cr_assert_not_null(n1);
    cr_assert_not_null(n2);
    n1->key = my_strdup("A");
    n1->value = my_strdup("1");
    n2->key = my_strdup("B");
    n2->value = NULL;
    n1->next = n2;
    n2->next = NULL;
    free_linked_list(n1);
}

Test(free_array, handles_null_array)
{
    free_array(NULL);
}

Test(free_array, frees_empty_array)
{
    char **arr = malloc(sizeof(char *));

    cr_assert_not_null(arr);
    arr[0] = NULL;
    free_array(arr);
}

Test(free_array, frees_populated_array)
{
    char **arr = malloc(sizeof(char *) * 3);

    cr_assert_not_null(arr);
    arr[0] = my_strdup("hello");
    arr[1] = my_strdup("world");
    arr[2] = NULL;
    free_array(arr);
}

Test(free_main, handles_null_stock)
{
    free_main(NULL);
}

Test(free_main, frees_fully_initialized_stock)
{
    extern char **environ;
    main_t *stock = init_main(environ);

    cr_assert_not_null(stock);
    free_main(stock);
}
