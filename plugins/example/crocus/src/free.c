/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#include "crocus.h"

int free_number(number_t *number)
{
    if (number) {
        if (number->line1)
	    free(number->line1);
        if (number->line2)
	   free(number->line2);
        if (number->line3)
	   free(number->line3);
        if (number->line4)
	   free(number->line4);
        if (number->line5)
	   free(number->line5);
	free(number);
    }
    return 0;
}

int free_crocus(crocus_t *crocus)
{
    if (crocus) {
        if (crocus->string)
            free(crocus->string);
        if (crocus->number)
            free(crocus->number);
	free(crocus);
    }
    return 0;
}
