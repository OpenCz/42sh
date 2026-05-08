/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#include "../include/crocus.h"

const tables_t TABLES[] = {
    {'0', zero},
    {'1', one},
    {'2', two},
    {'3', three},
    {'4', four},
    {'5', five},
    {'6', six},
    {'7', seven},
    {'8', eight},
    {'9', nine},
    {'\0', NULL}
};

static int fill_numbers(char number, number_t **numbers, int index)
{
    for (int i = 0; TABLES[i].number != '\0'; i++)
        if (number == TABLES[i].number)
            numbers[index] = TABLES[i].func();
    return 0;
}

static void print_end(number_t **numbers)
{
    for (int i = 0; numbers[i] != NULL; i++)
	if (numbers[i + 1] != NULL)
            printf("%s ", numbers[i]->line4);
        else
            printf("%s\n", numbers[i]->line4);
    for (int i = 0; numbers[i] != NULL; i++)
	if (numbers[i + 1] != NULL)
            printf("%s ", numbers[i]->line5);
        else
            printf("%s\n", numbers[i]->line5);
}

static int print_all(number_t **numbers)
{
    for (int i = 0; numbers[i] != NULL; i++)
	if (numbers[i + 1] != NULL)
            printf("%s ", numbers[i]->line1);
        else
            printf("%s\n", numbers[i]->line1);
    for (int i = 0; numbers[i] != NULL; i++)
	if (numbers[i + 1] != NULL)
            printf("%s ", numbers[i]->line2);
        else
            printf("%s\n", numbers[i]->line2);
    for (int i = 0; numbers[i] != NULL; i++)
	if (numbers[i + 1] != NULL)
            printf("%s ", numbers[i]->line3);
        else
            printf("%s\n", numbers[i]->line3);
   print_end(numbers);
   return 0;
}

int launch_crocus(crocus_t *crocus)
{
    number_t **numbers = NULL;
    int len = 0;

    for (; crocus->number[len] != '\0'; len++);
    numbers = malloc(sizeof(number_t) * (len + 1));
    if (!numbers)
        return 84;
    for (int i = 0; crocus->number[i] != '\0'; i++)
        if (fill_numbers(crocus->number[i], numbers, i) == 84) {
	    free(numbers);
            return 84;
        }
    numbers[len] = NULL;
    if (change_letter(crocus, numbers) == 84)
        return 84;
    print_all(numbers); 
    for (int i = 0; numbers[i] != NULL; i++)
        free_number(numbers[i]);
    free(numbers);
    return 0;
}

int crocus(int argc, char **argv)
{
    crocus_t *crocus = init_crocus();

    if (crocus == NULL)
        return 84;
    if (check_args(argc, argv, crocus) == 84 ||
        fill_null_string(crocus)) {
        free_crocus(crocus);
        return 84;
    }
    if (launch_crocus(crocus) == 84) {
        free_crocus(crocus);
	return 84;
    }
    free_crocus(crocus);
    return 0;
}
