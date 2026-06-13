#pragma once
#ifndef APP_H
#define APP_H

#include <raylib.h>

#define APP_NAME "Digit AI"
#define APP_VERSION "0.1.0"

#define GRID_SIZE 28
#define CELL_SIZE 25

#define WINDOW_WIDTH (GRID_SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE * CELL_SIZE)

typedef struct {
    float pixels[GRID_SIZE][GRID_SIZE];
} Canvas;

typedef struct {
    int is_mouse_down;
    Canvas canvas;
} App;

// App function declarations
void init_app(App *app);
void run_app(App *app);
void update_app(App *app);
void draw_app(App *app);
void destroy_app();

// Canvas function declarations
void draw_canvas(Canvas *canvas, int mouse_x, int mouse_y);
void clear_canvas(Canvas *canvas);
void render_canvas(Canvas *canvas);

#endif /* APP_H */