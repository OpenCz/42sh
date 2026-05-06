/*
** EPITECH PROJECT, 2026
** instaler
** File description:
** core
*/

#ifndef CORE_H
    #define CORE_H
    #include "../instaler.h"
typedef struct win_size_s {
    int x;
    int y;
}win_size_t;
typedef struct instaler_s {
    win_size_t size;
    WINDOW *window;
}instaler_t;
void loop(int c, instaler_t *instaler);
#endif
