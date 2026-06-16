#pragma once

#include <math.h>

#define INPUT_SIZE 784
#define HIDDEN_SIZE 64
#define OUTPUT_SIZE 10
#define LR 0.001f

typedef struct {
    float w1[INPUT_SIZE][HIDDEN_SIZE];
    float b1[HIDDEN_SIZE];

    float w2[HIDDEN_SIZE][OUTPUT_SIZE];
    float b2[OUTPUT_SIZE];
} NeuralNetwork;

float randf();

void nn_init(NeuralNetwork *nn);

void nn_forward(
    NeuralNetwork *nn,
    float input[INPUT_SIZE],
    float hidden[HIDDEN_SIZE],
    float output[OUTPUT_SIZE]
);

void nn_backprop(
    NeuralNetwork *nn,
    float input[INPUT_SIZE],
    float hidden[HIDDEN_SIZE],
    float output[OUTPUT_SIZE],
    int label
);

int nn_predict(float output[OUTPUT_SIZE]);

void softmax(float *input, float *output, int size);

float cross_entropy_loss(float output[OUTPUT_SIZE], int label);