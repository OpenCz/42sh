/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** inputs_alias_edit
*/

#include "../../include/instaler.h"

static void field_insert(char *buf, int *pos, int max, int c)
{
    int len = (int)strlen(buf);

    if (len >= max - 1)
        return;
    memmove(buf + *pos + 1, buf + *pos, (size_t)(len - *pos + 1));
    buf[*pos] = (char)c;
    (*pos)++;
}

static void field_backspace(char *buf, int *pos)
{
    int len = (int)strlen(buf);

    if (*pos == 0)
        return;
    memmove(buf + *pos - 1, buf + *pos, (size_t)(len - *pos + 1));
    (*pos)--;
}

static void field_delete_at(char *buf, int pos)
{
    int len = (int)strlen(buf);

    if (pos >= len)
        return;
    memmove(buf + pos, buf + pos + 1, (size_t)(len - pos));
}

static void apply_alias_edit(alias_t *a, alias_edit_t *e)
{
    strncpy(a->name, e->name, ALIAS_NAME_MAX - 1);
    a->name[ALIAS_NAME_MAX - 1] = '\0';
    strncpy(a->cmd, e->cmd, ALIAS_CMD_MAX - 1);
    a->cmd[ALIAS_CMD_MAX - 1] = '\0';
    a->enabled = true;
}

static void save_alias_edit(instaler_t *inst)
{
    alias_edit_t *e = &inst->alias_edit;
    preferences_t *p = &inst->prefs;
    int target;

    if (e->name[0] == '\0')
        return;
    if (e->idx == -1) {
        if (p->nb_aliases >= MAX_ALIASES)
            return;
        e->idx = p->nb_aliases;
        p->nb_aliases++;
    }
    target = e->idx;
    apply_alias_edit(&p->aliases[target], e);
    p->row = NB_PROMPT + 1 + target;
    if (target < p->alias_scroll)
        p->alias_scroll = target;
    if (target >= p->alias_scroll + ALIAS_VIEWPORT)
        p->alias_scroll = target - ALIAS_VIEWPORT + 1;
}

static void handle_field_keys(alias_edit_t *e, int c)
{
    char *buf = e->field == 0 ? e->name : e->cmd;
    int *pos = e->field == 0 ? &e->name_pos : &e->cmd_pos;
    int max = e->field == 0 ? ALIAS_NAME_MAX : ALIAS_CMD_MAX;
    int len = (int)strlen(buf);

    if (c == KEY_LEFT && *pos > 0)
        (*pos)--;
    if (c == KEY_RIGHT && *pos < len)
        (*pos)++;
    if (c == KEY_BACKSPACE || c == 127 || c == '\b')
        field_backspace(buf, pos);
    if (c == KEY_DC)
        field_delete_at(buf, *pos);
    if (c >= 32 && c < 127)
        field_insert(buf, pos, max, c);
}

void input_alias_edit(instaler_t *instaler, int c)
{
    alias_edit_t *e = &instaler->alias_edit;

    if (c == 27) {
        instaler->state = STEP_2;
        return;
    }
    if (c == '\n' || c == KEY_ENTER) {
        save_alias_edit(instaler);
        instaler->state = STEP_2;
        return;
    }
    if (c == '\t' || c == KEY_BTAB) {
        e->field = 1 - e->field;
        return;
    }
    handle_field_keys(e, c);
}
