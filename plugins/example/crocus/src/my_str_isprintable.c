/*
** EPITECH PROJECT, 2025
** my_str_isprintable
** File description:
** returns 1 if string contains only printable characters
*/

int my_str_isprintable(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++) {
        if (str[i] < 33 || str[i] > 126)
            return 0;
    }
    return 1;
}
