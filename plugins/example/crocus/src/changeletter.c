/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#include "crocus.h"

void change_line_five(crocus_t *crocus, number_t **numbers, int i)
{
    int value = crocus->number[i] - '0';

    for (int j = 0; numbers[i]->line1[j] != '\0'; j++)
        if (numbers[i]->line5[j] == '0')
            numbers[i]->line5[j] = crocus->string[value % strlen(crocus->string)];
}

void change_line_four(crocus_t *crocus, number_t **numbers, int i)
{
    int value = crocus->number[i] - '0';

    for (int j = 0; numbers[i]->line1[j] != '\0'; j++)
        if (numbers[i]->line4[j] == '0')
            numbers[i]->line4[j] = crocus->string[value % strlen(crocus->string)];
}

void change_line_third(crocus_t *crocus, number_t **numbers, int i)
{
    int value = crocus->number[i] - '0';

    for (int j = 0; numbers[i]->line1[j] != '\0'; j++)
        if (numbers[i]->line3[j] == '0')
            numbers[i]->line3[j] = crocus->string[value % strlen(crocus->string)]; 
}

void change_line_two(crocus_t *crocus, number_t **numbers, int i)
{
    int value = crocus->number[i] - '0';

    for (int j = 0; numbers[i]->line1[j] != '\0'; j++)
        if (numbers[i]->line2[j] == '0')
            numbers[i]->line2[j] = crocus->string[value % strlen(crocus->string)]; 
}

void change_line_one(crocus_t *crocus, number_t **numbers, int i)
{
    int value = crocus->number[i] - '0';

    for (int j = 0; numbers[i]->line1[j] != '\0'; j++)
        if (numbers[i]->line1[j] == '0')
            numbers[i]->line1[j] = crocus->string[value % strlen(crocus->string)];
}

int change_letter(crocus_t *crocus, number_t **numbers)
{
    for (int i = 0; numbers[i] != NULL; i++) { 
        change_line_one(crocus, numbers, i);
        change_line_two(crocus, numbers, i);
        change_line_third(crocus, numbers, i);
        change_line_four(crocus, numbers, i);
        change_line_five(crocus, numbers, i);
    }
    return 0;
}
