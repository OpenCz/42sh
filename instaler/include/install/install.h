/*
** EPITECH PROJECT, 2026
** 42SH
** File description:
** install
*/

#ifndef INSTALL_H
    #define INSTALL_H
    #include "../instaler.h"
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
