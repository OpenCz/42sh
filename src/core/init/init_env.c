/*
** EPITECH PROJECT, 2026
** env
** File description:
** env
*/

#include "minishell.h"

static env_t *create_env_node(char *env_string)
{
    env_t *node;
    char **stock;

    stock = my_str_to_word_array(env_string, "=");
    if (!stock)
        return NULL;
    node = malloc(sizeof(env_t));
    if (!node)
        return NULL;
    node->key = stock[0];
    node->value = stock[1] ? stock[1] : NULL;
    node->next = NULL;
    free(stock);
    return node;
}

env_t *init_env(char **env)
{
    env_t *head = NULL;
    env_t *current = NULL;
    env_t *node;
    int i;

    for (i = 0; env[i] != NULL; i++) {
        node = create_env_node(env[i]);
        if (!node)
            return NULL;
        if (head == NULL) {
            head = node;
            current = node;
        } else {
            current->next = node;
            current = node;
        }
    }
    return head;
}
