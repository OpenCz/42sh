/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** File size query: get_file_size_stat calls stat() on a filepath
** and returns st_size in bytes on success, or -1 on error.
** Used by openator() to pre-allocate an exact-size read buffer.
** Authors: @Celz-Pch @Lukas-sgx @ErwanTheKing @sacha-lma @Jessymgadd
*/

#include <sys/stat.h>
#include <unistd.h>
#include "c_zsh.h"

int get_file_size_stat(char const *filepath)
{
    struct stat statstruct;

    if (filepath == NULL) {
        write(2, "NULL FILEPATH\n", 14);
        return -1;
    }
    if (stat(filepath, &statstruct) == -1) {
        write(2, "STAT FAILURE\n", 13);
        return -1;
    }
    return statstruct.st_size;
}
