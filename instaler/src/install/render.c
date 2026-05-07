/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** render
*/

#include "../../include/instaler.h"

static void render_toggle(instaler_t *inst, int r, int y, int x)
{
    preferences_t *p = &inst->prefs;
    prompt_item_t *item = &p->prompt[r];

    if (p->row == r && p->col == 0)
        attron(A_REVERSE);
    mvprintw(y, x, " [%c] %-12s", item->enabled ? 'x' : ' ', item->key);
    if (p->row == r && p->col == 0)
        attroff(A_REVERSE);
}

static void render_colors(instaler_t *inst, int r)
{
    preferences_t *p = &inst->prefs;
    prompt_item_t *item = &p->prompt[r];

    if (p->row == r && p->col == 1)
        attron(A_REVERSE);
    printw("fg: %-12s", get_cycle_color(item->fg));
    if (p->row == r && p->col == 1)
        attroff(A_REVERSE);
    if (p->row == r && p->col == 2)
        attron(A_REVERSE);
    printw("bg: %-12s", get_cycle_color(item->bg));
    if (p->row == r && p->col == 2)
        attroff(A_REVERSE);
}

static void render_prompt_row(instaler_t *inst, int r, int y, int x)
{
    render_toggle(inst, r, y, x);
    render_colors(inst, r);
}

static void render_date_row(instaler_t *inst, int y, int x)
{
    preferences_t *p = &inst->prefs;

    if (p->row == NB_PROMPT)
        attron(A_REVERSE);
    mvprintw(y, x, " date_format : %-6s < LEFT/RIGHT >",
        get_date_fmt_str(p->date_fmt));
    if (p->row == NB_PROMPT)
        attroff(A_REVERSE);
}

static void render_alias_row(instaler_t *inst, int alias_idx, int y, int x)
{
    preferences_t *p = &inst->prefs;
    alias_t *a = &p->aliases[alias_idx];
    int row_idx = NB_PROMPT + 1 + alias_idx;

    if (p->row == row_idx)
        attron(A_REVERSE);
    mvprintw(y, x, " [%c] %-10s  %s",
        a->enabled ? 'x' : ' ', a->name, a->cmd);
    if (p->row == row_idx)
        attroff(A_REVERSE);
}

static void render_add_alias_btn(instaler_t *inst, int y, int x)
{
    preferences_t *p = &inst->prefs;

    if (p->row == NB_PROMPT + p->nb_aliases + 1)
        attron(A_REVERSE);
    mvprintw(y, x, "  [ + Add alias ]  ");
    if (p->row == NB_PROMPT + p->nb_aliases + 1)
        attroff(A_REVERSE);
}

static void render_install_btn(instaler_t *inst, int y, int x)
{
    preferences_t *p = &inst->prefs;

    if (p->row == NB_PROMPT + p->nb_aliases + 2)
        attron(A_REVERSE);
    mvprintw(y, x + 12, "  [ Install ]  ");
    if (p->row == NB_PROMPT + p->nb_aliases + 2)
        attroff(A_REVERSE);
}

static void render_hint(instaler_t *inst)
{
    preferences_t *p = &inst->prefs;
    int alias_start = NB_PROMPT + 1;
    int alias_end = NB_PROMPT + p->nb_aliases;

    if (p->row < NB_PROMPT)
        mvprintw(inst->size.y - 2, 0,
            "UP/DOWN:row  LEFT/RIGHT:color  TAB:col  SPACE:toggle");
    if (p->row >= alias_start && p->row <= alias_end)
        mvprintw(inst->size.y - 2, 0,
            "UP/DOWN:row  SPACE:toggle  D:delete  E:edit");
    if (p->row == NB_PROMPT + p->nb_aliases + 1)
        mvprintw(inst->size.y - 2, 0, "ENTER: add new alias");
    if (p->row == NB_PROMPT + p->nb_aliases + 2)
        mvprintw(inst->size.y - 2, 0, "ENTER: install");
}

static void render_alias_section(instaler_t *inst, int y, int x)
{
    preferences_t *p = &inst->prefs;
    int idx;

    mvprintw(y, x, "[alias]");
    if (p->alias_scroll > 0)
        mvprintw(y, x + 10, "(^)");
    y++;
    for (int i = 0; i < ALIAS_VIEWPORT; i++) {
        idx = p->alias_scroll + i;
        if (idx < p->nb_aliases)
            render_alias_row(inst, idx, y + i, x);
    }
    if (p->alias_scroll + ALIAS_VIEWPORT < p->nb_aliases)
        mvprintw(y + ALIAS_VIEWPORT, x, "(v)");
    render_add_alias_btn(inst, y + ALIAS_VIEWPORT + 1, x);
    render_install_btn(inst, y + ALIAS_VIEWPORT + 3, x);
}

void render_preferences(instaler_t *instaler)
{
    int cy = instaler->size.y / 2 - 12;
    int cx = instaler->size.x / 2 - 25;

    if (cy < 2)
        cy = 2;
    mvprintw(cy - 2, cx, "Custom Install - Configure preferences:");
    mvprintw(cy - 1, cx, "[prompt]");
    for (int i = 0; i < NB_PROMPT; i++)
        render_prompt_row(instaler, i, cy + i * 2, cx);
    render_date_row(instaler, cy + NB_PROMPT * 2, cx);
    render_alias_section(instaler, cy + NB_PROMPT * 2 + 2, cx);
    render_hint(instaler);
    mvprintw(instaler->size.y - 1, 0, "Press 'q' to quit.");
}
