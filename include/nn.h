#pragma once
#ifndef NN_H
#define NN_H

#include <stdlib.h>

typedef struct {
    float w1[784][64];
    float b1[64];

    float w2[64][10];
    float b2[10];
} NeuralNetwork;

float randf();
void nn_init(NeuralNetwork *nn);
float relu(float x);
int nn_forward(NeuralNetwork *nn, float input[784]);

#endif
