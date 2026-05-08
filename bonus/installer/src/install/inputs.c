/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** inputs
*/

#include "installer/install.h"

static void handle_prompt_input(instaler_t *inst, int c)
{
    preferences_t *p = &inst->prefs;
    prompt_item_t *item = &p->prompt[p->row];
    int dir = (c == KEY_LEFT) ? -1 : 1;

    if (c == ' ')
        p->prompt[p->row].enabled = !p->prompt[p->row].enabled;
    if (c == '\t')
        p->col = (p->col + 1) % 3;
    if (c == KEY_BTAB)
        p->col = (p->col + 2) % 3;
    if ((c == KEY_LEFT || c == KEY_RIGHT) && p->col == 1)
        item->fg = (item->fg + dir + NB_CYCLE_COLORS) % NB_CYCLE_COLORS;
    if ((c == KEY_LEFT || c == KEY_RIGHT) && p->col == 2)
        item->bg = (item->bg + dir + NB_CYCLE_COLORS) % NB_CYCLE_COLORS;
}

static void handle_date_input(instaler_t *inst, int c)
{
    preferences_t *p = &inst->prefs;
    int dir = (c == KEY_LEFT) ? -1 : 1;

    if (c == KEY_LEFT || c == KEY_RIGHT)
        p->date_fmt = (p->date_fmt + dir + NB_DATE_FMTS) % NB_DATE_FMTS;
}

static void delete_alias(preferences_t *p, int idx)
{
    int i;
    int max_row;

    for (i = idx; i < p->nb_aliases - 1; i++)
        p->aliases[i] = p->aliases[i + 1];
    p->nb_aliases--;
    if (p->alias_scroll >= p->nb_aliases && p->alias_scroll > 0)
        p->alias_scroll--;
    max_row = NB_PROMPT + p->nb_aliases + 2;
    if (p->row > max_row)
        p->row = max_row;
}

static void open_alias_edit(instaler_t *inst, int alias_idx)
{
    alias_edit_t *e = &inst->alias_edit;
    preferences_t *p = &inst->prefs;

    e->idx = alias_idx;
    e->field = 0;
    if (alias_idx == -1) {
        e->name[0] = '\0';
        e->cmd[0] = '\0';
        e->name_pos = 0;
        e->cmd_pos = 0;
    } else {
        strncpy(e->name, p->aliases[alias_idx].name, ALIAS_NAME_MAX - 1);
        e->name[ALIAS_NAME_MAX - 1] = '\0';
        strncpy(e->cmd, p->aliases[alias_idx].cmd, ALIAS_CMD_MAX - 1);
        e->cmd[ALIAS_CMD_MAX - 1] = '\0';
        e->name_pos = (int)strlen(e->name);
        e->cmd_pos = (int)strlen(e->cmd);
    }
    inst->state = ALIAS_EDIT;
}

static void handle_alias_input(instaler_t *inst, int c)
{
    preferences_t *p = &inst->prefs;
    int idx = p->row - NB_PROMPT - 1;

    if (idx < 0 || idx >= p->nb_aliases)
        return;
    if (c == ' ')
        p->aliases[idx].enabled = !p->aliases[idx].enabled;
    if ((c == 'd' || c == 'D') && p->nb_aliases > 0)
        delete_alias(p, idx);
    if (c == 'e' || c == 'E' || c == '\n' || c == KEY_ENTER)
        open_alias_edit(inst, idx);
}

static void handle_add_alias_input(instaler_t *inst, int c)
{
    preferences_t *p = &inst->prefs;

    if (p->row != NB_PROMPT + p->nb_aliases + 1)
        return;
    if (c == '\n' || c == KEY_ENTER)
        open_alias_edit(inst, -1);
}

static void handle_install_input(instaler_t *inst, int c)
{
    preferences_t *p = &inst->prefs;

    if (p->row != NB_PROMPT + p->nb_aliases + 2)
        return;
    if (c == '\n' || c == KEY_ENTER) {
        write_rc(p);
        inst->state = DONE;
    }
}

static void update_alias_scroll(preferences_t *p)
{
    int alias_idx = p->row - NB_PROMPT - 1;

    if (alias_idx < 0 || alias_idx >= p->nb_aliases)
        return;
    if (alias_idx < p->alias_scroll)
        p->alias_scroll = alias_idx;
    if (alias_idx >= p->alias_scroll + ALIAS_VIEWPORT)
        p->alias_scroll = alias_idx - ALIAS_VIEWPORT + 1;
}

void input_preferences(instaler_t *instaler, int c)
{
    preferences_t *p = &instaler->prefs;
    int max_row = NB_PROMPT + p->nb_aliases + 2;

    if (c == KEY_UP && p->row > 0)
        p->row--;
    if (c == KEY_DOWN && p->row < max_row)
        p->row++;
    update_alias_scroll(p);
    if (p->row >= NB_PROMPT && p->col > 0)
        p->col = 0;
    if (p->row < NB_PROMPT)
        handle_prompt_input(instaler, c);
    if (p->row == NB_PROMPT)
        handle_date_input(instaler, c);
    if (p->row > NB_PROMPT && p->row <= NB_PROMPT + p->nb_aliases)
        handle_alias_input(instaler, c);
    handle_add_alias_input(instaler, c);
    handle_install_input(instaler, c);
}
