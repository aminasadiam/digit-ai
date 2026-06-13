#pragma once
#ifndef CANVAS_H
#define CANVAS_H

#include <raylib.h>

#define GRID_SIZE 28

typedef struct {
    float pixels[GRID_SIZE][GRID_SIZE];
    int cell_size;
} Canvas;

void init_canvas(Canvas *canvas, int window_width);
void draw_canvas(Canvas *canvas, int mouse_x, int mouse_y);
void clear_canvas(Canvas *canvas);
void render_canvas(Canvas *canvas);

void canvas_to_input(const Canvas *canvas, float *input);

#endif /* CANVAS_H */