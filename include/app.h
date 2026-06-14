#pragma once
#ifndef APP_H
#define APP_H

#include <raylib.h>
#include "canvas.h"

#define APP_NAME "Digit AI"

#define GRID_SIZE 28
#define CELL_SIZE 25

#define WINDOW_WIDTH (GRID_SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE * CELL_SIZE)

typedef struct {
    int is_mouse_down;
    float input[GRID_SIZE * GRID_SIZE];
    Canvas canvas;
} App;


void init_app(App *app);
void run_app(App *app);
void update_app(App *app);
void draw_app(App *app);
void destroy_app();

void output_input(const App *app);

#endif /* APP_H */
