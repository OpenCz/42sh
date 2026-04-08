/*
** EPITECH PROJECT, 2025
** bootstrap
** File description:
** get_file_size
*/

#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"

int get_file_size_stat(char const *filepath)
{
    struct stat statstruct;

    if (filepath == NULL) {
        write(2, "NULL FILEPATH\n", 14);
        return FAILURE;
    }
    if (stat(filepath, &statstruct) == -1) {
        write(2, "STAT FAILURE\n", 13);
        return FAILURE;
    }
    return statstruct.st_size;
}
