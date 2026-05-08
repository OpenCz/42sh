/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** instaler
*/

#ifndef INSTALER_H
    #define INSTALER_H
    #include <ncurses.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <stdio.h>
    #include "utils/utils.h"
    #include "init/init.h"
    #include "core/core.h"
    #include "display/display.h"

char *detect_os(void);
char *get_cycle_color(int i);
char *get_date_fmt_str(date_fmt_t fmt);
void init_preferences(instaler_t *instaler);
void write_rc(preferences_t *prefs);
void render_preferences(instaler_t *instaler);
void render_alias_edit(instaler_t *instaler);
void input_preferences(instaler_t *instaler, int c);
void input_alias_edit(instaler_t *instaler, int c);
#endif
