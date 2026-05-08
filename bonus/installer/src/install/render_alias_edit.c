/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** render_alias_edit
*/

#include "installer/install.h"

static void render_edit_field(alias_edit_t *e, int field, int y, int x)
{
    char *label = field == 0 ? "Name" : "Cmd";
    char *buf = field == 0 ? e->name : e->cmd;
    int pos = field == 0 ? e->name_pos : e->cmd_pos;
    bool focused = (e->field == field);
    int field_w = 40;
    int len = (int)strlen(buf);

    mvprintw(y, x, "%-6s [", label);
    for (int i = 0; i < field_w; i++) {
        if (focused && i == pos)
            attron(A_REVERSE);
        addch((i < len) ? (unsigned char)buf[i] : ' ');
        if (focused && i == pos)
            attroff(A_REVERSE);
    }
    addch(']');
}

void render_alias_edit(instaler_t *instaler)
{
    alias_edit_t *e = &instaler->alias_edit;
    int cy = instaler->size.y / 2 - 3;
    int cx = instaler->size.x / 2 - 26;
    char *title = e->idx == -1 ? "Add alias" : "Edit alias";

    mvprintw(cy, cx, "--- %s ---", title);
    render_edit_field(e, 0, cy + 2, cx);
    render_edit_field(e, 1, cy + 3, cx);
    mvprintw(cy + 5, cx, "TAB: next field   ENTER: save   ESC: cancel");
}
