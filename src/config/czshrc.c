/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** czshrc
*/

#include "../../include/c_zsh.h"

static void parse_and_fill_struct(czshrc_t *rc, char *rc_content)
{
    char ***rc_parsed = my_str_to_array_of_word_array(rc_content, "\n", "=");

    for (int i = 0; rc_parsed[i]; i++) {
        if (rc_parsed[i][0][0] == '#')
            continue;
        if (my_strcmp(rc_parsed[i][0], "[prompt]") == 0)
            manage_prompt(rc, rc_parsed, i);
    }
}

czshrc_t *update_rc(void)
{
    czshrc_t *rc = malloc(sizeof(czshrc_t));
    char *rc_content = NULL;

    if (!rc)
        return NULL;
    if (access(".czshrc", F_OK) == -1) {
        set_default_rc(rc);
        return rc;
    }
    rc_content = openator(".czshrc");
    if (!rc_content) {
        set_default_rc(rc);
        return rc;
    }
    parse_and_fill_struct(rc, rc_content);
    return rc;
}
