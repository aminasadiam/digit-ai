#pragma once

#include <raylib.h>
#include "canvas.h"
#include "nn.h"
#include "mnist.h"

#define APP_NAME "Digit AI"

#define GRID_SIZE 28
#define CELL_SIZE 25

#define WINDOW_WIDTH (GRID_SIZE * CELL_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE * CELL_SIZE)

#define MAX_TRAIN_SAMPLES 60000
#define MAX_TEST_SAMPLES 10000

typedef struct {
    Canvas canvas;
    NeuralNetwork nn;

    MnistSample *train_set;
    int train_count;

    MnistSample *test_set;
    int test_count;

    float input[GRID_SIZE * GRID_SIZE];
    float hidden[64];
    float output[10];

    float loss;

    int predicted;

    int dirty;
    int frame;

    int training;
    int epoch;
} App;

void init_app(App *app);
void run_app(App *app);
void update_app(App *app);
void draw_app(App *app);
void destroy_app(App *app);

void draw_output(const App *app);
void draw_input_debug(const App *app);

void train_one_epoch(App *app);
void evaluate(App *app);