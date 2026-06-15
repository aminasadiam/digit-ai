#pragma once
#ifndef APP_H
#define APP_H

#include <raylib.h>
#include "canvas.h"
#include "nn.h"

#define APP_NAME "Digit AI"

#define GRID_SIZE 28
#define CELL_SIZE 25

#define WINDOW_WIDTH (GRID_SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE * CELL_SIZE)

typedef struct {
    Canvas canvas;
    NeuralNetwork nn;

    float input[GRID_SIZE * GRID_SIZE];
    float hidden[64];
    float output[10];

    int predicted;

    int dirty;
    int frame;
} App;

void init_app(App *app);
void run_app(App *app);
void update_app(App *app);
void draw_app(App *app);
void destroy_app();

void draw_output(const App *app);
void draw_input_debug(const App *app);

#endif
