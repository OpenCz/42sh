/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/pre-release/minishell
** File description:
** mysh
*/

#include "crocus.h"

static int fill_string(crocus_t *crocus, char *str)
{
    if (!my_str_isprintable(str) ||
        crocus->is_string_arg == 1)
        return 84;
    crocus->string = strdup(str);
    crocus->is_string_arg = 1;
    return 0;
}

static int fill_number(crocus_t *crocus, char *str)
{
    if (!my_str_isnum(str) ||
        crocus->is_number_arg == 1)
        return 84;
    crocus->number = strdup(str);
    crocus->is_number_arg = 1;
    return 0;
}

int fill_args(char **argv, int i, crocus_t *crocus)
{
    if (strcmp("-n", argv[i]) == 0)
         if (!argv[i + 1] || fill_number(crocus, argv[i + 1]) == 84)
	    return 84;
    if (strcmp("-s", argv[i]) == 0)
        if (!argv[i + 1] || fill_string(crocus, argv[i + 1]) == 84)
	    return 84;
    return 0;
 }

int check_args(int argc, char **argv, crocus_t *crocus)
{
    for (int i = 1; argv[i] != NULL && i <= argc; i++)
        fill_args(argv, i, crocus);
    if (crocus->is_number_arg == 0)
        return 84;
    return 0;
}

crocus_t *init_crocus(void)
{
    crocus_t *crocus = malloc(sizeof(crocus_t));

    if (crocus == NULL)
        return NULL;
    crocus->is_string_arg = 0;
    crocus->is_number_arg = 0;
    crocus->number = 0;
    crocus->string = NULL;
    return crocus;
}

int fill_null_string(crocus_t *crocus)
{
    if (crocus->is_string_arg == 0) {
        crocus->string = strdup("0");
        if (!crocus->string) {
            free_crocus(crocus);
	    return 84;
        }
    }
    return 0;
}
