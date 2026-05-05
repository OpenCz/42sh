/*
** EPITECH PROJECT, 2026
** ~/epitech/delivery/42sh/src/core/context
** File description:
** autocomplete.c
*/

#include "c_zsh.h"

static void append_bin(char *buffer, struct dirent *file, char *path,
    char ***names)
{
    char *bin = NULL;

    if (strncmp(buffer, file->d_name, strlen(buffer)) == 0) {
        bin = check_bin(file->d_name, path);
        if (bin) {
            append_array(names, file->d_name);
            free_alloc(bin);
        }
    }
}

char **find_name_executables(char *buffer, char *path)
{
    DIR *directory = opendir(path);
    struct dirent *file = NULL;
    char **names = NULL;

    if (!directory)
        return NULL;
    for (file = readdir(directory); file != NULL; file = readdir(directory))
        append_bin(buffer, file, path, &names);
    if (closedir(directory) == -1)
        return NULL;
    return names;
}

static void delete_element(int i, int j, char ***names)
{
    if (strcmp((*names)[i], (*names)[j]) == 0) {
        free_alloc((*names)[j]);
        for (int k = j; (*names)[k] != NULL; k++)
            (*names)[k] = (*names)[k + 1];
        j--;
    }
}

static void clean_multiple(char ***names)
{
    int i = 0;
    int j = 0;

    if (!names || !*names)
        return;
    for (i = 0; (*names)[i] != NULL; i++)
        for (j = i + 1; (*names)[j] != NULL; j++)
            delete_element(i, j, names);
}

char **get_auto_exec(char *word, env_t *env, int *cursor)
{
    char **path = my_str_to_word_array(get_path(env), ":");
    char **total = NULL;

    if (!path || !word)
        return NULL;
    for (int i = 0; path[i] != NULL; i++)
        append_array_to_array(&total, find_name_executables(word, path[i]));
    free_array(path);
    clean_multiple(&total);
    return total;
}

int menu(char **names, main_t *stock_main)
{
    char arrow[3] = {0};

    if (read(STDIN_FILENO, &arrow[0], 1) == 1 && arrow[0] == '\e' &&
        read(STDIN_FILENO, &arrow[1], 1) == 1 && arrow[1] == '[' &&
        read(STDIN_FILENO, &arrow[2], 1) == 1 && arrow[2] == 'B') {
        write(STDOUT_FILENO, "\n\e[1m⇒\e[m\n",
            sizeof("\n\e[1m⇒\e[m\n") - 1);
    }
    display_prompt(stock_main->czshrc->prompt, get_user(stock_main->stock_env));
    return 0;
}

void ask_see_command(char **names, main_t *stock_main)
{
    struct termios old;
    struct termios tr;
    char answer = 0;

    printf("\nThere is %i commands available, do you want to see it (Y/n)\n", len_array(names));
    tcgetattr(STDIN_FILENO, &old);
    tr = old;
    tr.c_lflag &= ~(ICANON | ECHO);
    tr.c_cc[VMIN] = 1;
    tr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &tr);
    if (read(STDIN_FILENO, &answer, 1) == 1) {
        if (answer == 'Y' || answer == 'y' || answer == '\n') {
            tcsetattr(STDIN_FILENO, TCSANOW, &old);
            menu(names, stock_main);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &old);
            display_prompt(stock_main->czshrc->prompt, get_user(stock_main->stock_env));
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
}

int complete_menu(char **names, main_t *stock_main)
{
    if (len_array(names) >= 100)
        ask_see_command(names, stock_main);
    else if (len_array(names) > 1)
        menu(names, stock_main);
    return 0;
}

int handle_autocomplete(char **buffer, int *len, int *cursor,
    main_t *main_stock)
{
    char **names = NULL;
    char *word = get_word_on_cursor(buffer, cursor);

    if (*len <= 0 || !word)
        return 0;
    names = get_auto_exec(word, main_stock->stock_env, cursor);
    if (!names) {
        free_alloc(word);
        return 0;
    }
    for (int i = 0; names[i] != NULL; i++) {
        if (strcmp(names[i], word) == 0) {
            strcat(*buffer, " ");
            (*len)++;
            (*cursor)++;
            free_array(names);
            free_alloc(word);
            return 0;
        }
    }
    complete_menu(names, main_stock);
    free_array(names);
    free_alloc(word);
    return 0;
}
