/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** loop
*/

#include "../../../include/instaler.h"

static void manage_step_1(instaler_t *instaler)
{
    mvprintw(instaler->size.y / 2, instaler->size.x / 2 - 15,
        "1: quick instal");
    mvprintw(instaler->size.y / 2 + 2, instaler->size.x / 2 - 15,
        "2: custom instal");
}

static void manage_quick(instaler_t *instaler)
{
    init_preferences(instaler);
    write_rc(&instaler->prefs);
    instaler->state = DONE;
}

static void manage_done(instaler_t *instaler)
{
    mvprintw(instaler->size.y / 2, instaler->size.x / 2 - 20,
        "Installation complete! Press any key to exit.");
}

static void manage_steps(instaler_t *instaler)
{
    if (instaler->state == STEP_1)
        manage_step_1(instaler);
    if (instaler->state == STEP_2)
        render_preferences(instaler);
    if (instaler->state == ALIAS_EDIT)
        render_alias_edit(instaler);
    if (instaler->state == QUICK)
        manage_quick(instaler);
    if (instaler->state == DONE)
        manage_done(instaler);
}

static void manage_inputs(instaler_t *instaler, int c)
{
    if (instaler->state == STEP_1 && c == '2') {
        init_preferences(instaler);
        instaler->state = STEP_2;
    }
    if (instaler->state == STEP_1 && c == '1')
        instaler->state = QUICK;
    if (instaler->state == STEP_2)
        input_preferences(instaler, c);
    else if (instaler->state == ALIAS_EDIT)
        input_alias_edit(instaler, c);
    if (instaler->state == DONE && c != ERR)
        instaler->state = END;
}

static bool run_iteration(instaler_t *instaler, char **title_arr)
{
    int c;

    clear();
    manage_steps(instaler);
    print_ascii(1, 15, title_arr);
    if (instaler->state == STEP_1)
        mvprintw(instaler->size.y - 1, 0, "Press 'q' to quit.");
    refresh();
    c = getch();
    if (c == 'q' && instaler->state != ALIAS_EDIT)
        return false;
    manage_inputs(instaler, c);
    return true;
}

void loop(instaler_t *instaler)
{
    char *title_str = openator("assets/title.txt");
    char **title_arr = title_str ?
        my_str_to_word_array(title_str, "\n") : NULL;

    if (!title_arr) {
        free_alloc(title_str);
        return;
    }
    while (instaler->state != END && run_iteration(instaler, title_arr));
    free_array(title_arr);
    free_alloc(title_str);
}
