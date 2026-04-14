/*
** EPITECH PROJECT, 2026
** env
** File description:
** env
*/

#include "42sh.h"

static char *dup_n(char *src, int n)
{
    char *copy = malloc(sizeof(char) * (n + 1));

    if (!copy)
        return NULL;
    for (int i = 0; i < n; i++)
        copy[i] = src[i];
    copy[n] = '\0';
    return copy;
}

static int set_env_value(env_t *node, char *env_string, int sep)
{
    if (env_string[sep] != '=') {
        node->value = NULL;
        return SUCCESS;
    }
    node->value = my_strdup(env_string + sep + 1);
    return node->value == NULL;
}

static env_t *alloc_env_node(char *env_string, int sep)
{
    env_t *node = malloc(sizeof(env_t));

    if (!node)
        return NULL;
    node->key = dup_n(env_string, sep);
    if (!node->key) {
        free(node);
        return NULL;
    }
    return node;
}

static env_t *create_env_node(char *env_string)
{
    env_t *node;
    int sep = 0;

    if (!env_string)
        return NULL;
    while (env_string[sep] && env_string[sep] != '=')
        sep++;
    node = alloc_env_node(env_string, sep);
    if (!node)
        return NULL;
    if (set_env_value(node, env_string, sep)) {
        free(node->key);
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

static void append_env_node(env_t **head, env_t **current, env_t *node)
{
    if (*head == NULL) {
        *head = node;
        *current = node;
    } else {
        (*current)->next = node;
        *current = node;
    }
}

static int init_default_env(env_t **head, env_t **current, char **env)
{
    env_t *node;
    bool has_path = false;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0) {
            has_path = true;
            break;
        }
    }
    if (has_path)
        return 0;
    node = create_env_node("PATH=/bin:/usr/bin");
    if (!node)
        return 1;
    append_env_node(head, current, node);
    return 0;
}

env_t *init_env(char **env)
{
    env_t *head = NULL;
    env_t *current = NULL;
    env_t *node;
    int i;

    if (init_default_env(&head, &current, env))
        return NULL;
    for (i = 0; env[i] != NULL; i++) {
        node = create_env_node(env[i]);
        if (!node)
            return NULL;
        append_env_node(&head, &current, node);
    }
    return head;
}
