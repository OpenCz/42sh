/*
** EPITECH PROJECT, 2025
** bootstrap_setting_up
** File description:
** openator
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../../include/minishell.h"

int check_open(int fd)
{
    if (fd < 0) {
        write(2, "FAILURE IN OPEN : FILE NOT FOUND OR DOESN'T EXIST\n",
            50);
        return 84;
    }
    return 0;
}

int check_read(char *buffer, int bytes_read)
{
    if (bytes_read < 0) {
        write(2, "READ FAILURE\n", 13);
        free(buffer);
        return 84;
    }
    if (bytes_read == 0) {
        write(2, "FILE IS EMPTY\n", 14);
        free(buffer);
        return 84;
    }
    return 0;
}

int check_buffer(char *buffer)
{
    if (!buffer) {
        write(2, "BUFFER MEMORY ALLOCATION FAILURE\n", 34);
        return 84;
    }
    return 0;
}

static char *read_content(int fd, int size)
{
    char *buffer;
    int bytes_read;

    buffer = malloc(sizeof(char) * (size + 1));
    if (check_buffer(buffer) == 84) {
        close(fd);
        return NULL;
    }
    bytes_read = read(fd, buffer, size);
    if (check_read(buffer, bytes_read) == 84) {
        close(fd);
        return NULL;
    }
    buffer[bytes_read] = '\0';
    close(fd);
    return buffer;
}

char *openator(char const *filepath)
{
    int fd;
    int size;

    if (filepath == NULL) {
        write(2, "NULL FILEPATH\n", 14);
        return NULL;
    }
    fd = open(filepath, O_RDONLY);
    if (check_open(fd) == 84)
        return NULL;
    size = get_file_size_stat(filepath);
    return read_content(fd, size);
}
