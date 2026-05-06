/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/utils/strings
** File description:
** array.c
*/

#include "c_zsh.h"

int len_array(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i] != NULL; i++);
    return i;
}

void append_array(char ***array, char *name)
{
    char **new_array = NULL;
    int len = len_array(*array);

    if (!(*array)) {
        *array = malloc(sizeof(char *) * 2);
        if (!*array)
            return;
        (*array)[0] = strdup(name);
        (*array)[1] = NULL;
    } else {
        new_array = realloc(*array, sizeof(char *) * (len + 2));
        if (!new_array)
            return;
        *array = new_array;
        (*array)[len] = strdup(name);
        (*array)[len + 1] = NULL;
    }
}

void append_array_to_array(char ***array, char **array2)
{
    char **new_array = NULL;
    int idx = 0;
    int len_array1 = len_array(*array);
    int len_array2 = len_array(array2);

    if (!array2)
        return;
    if (!(*array)) {
        *array = array2;
        return;
    }
    new_array = realloc(*array, sizeof(char *) * (len_array1 + len_array2 + 1));
    if (!new_array)
        return;
    *array = new_array;
    for (; array2[idx] != NULL; idx++)
        (*array)[len_array1 + idx] = array2[idx];
    (*array)[len_array1 + idx] = NULL;
    free_alloc(array2);
}

static void merge_remaining(char **array, char **left_array,
    char **right_array, int *idx)
{
    while (idx[0] < idx[3]) {
        array[idx[2]] = left_array[idx[0]];
        idx[0]++;
        idx[2]++;
    }
    while (idx[1] < idx[4]) {
        array[idx[2]] = right_array[idx[1]];
        idx[1]++;
        idx[2]++;
    }
}

static void merge_fill(char **array, char **left_array,
    char **right_array, int *idx)
{
    while (idx[0] < idx[3] && idx[1] < idx[4]) {
        if (strcmp(left_array[idx[0]], right_array[idx[1]]) <= 0) {
            array[idx[2]] = left_array[idx[0]];
            idx[0]++;
        } else {
            array[idx[2]] = right_array[idx[1]];
            idx[1]++;
        }
        idx[2]++;
    }
    merge_remaining(array, left_array, right_array, idx);
}

static void merge(char **array, int left, int mid, int right)
{
    char **left_array = malloc(sizeof(char *) * (mid - left + 1));
    char **right_array = malloc(sizeof(char *) * (right - mid));
    int idx[5] = {0, 0, left, mid - left + 1, right - mid};

    if (!left_array || !right_array)
        return;
    for (int i = 0; i < mid - left + 1; i++)
        left_array[i] = array[left + i];
    for (int i = 0; i < right - mid; i++)
        right_array[i] = array[mid + 1 + i];
    merge_fill(array, left_array, right_array, idx);
    free_alloc(left_array);
    free_alloc(right_array);
}

void merge_sort(char **array, int left, int right)
{
    int mid = left + (right - left) / 2;

    if (left >= right)
        return;
    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);
    merge(array, left, mid, right);
}
