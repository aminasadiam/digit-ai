#include "nn.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

float randf()
{
    return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
}

static float xavier_limit(int fan_in, int fan_out)
{
    return sqrtf(6.0f / (fan_in + fan_out));
}

void nn_init(NeuralNetwork *nn)
{
    srand((unsigned int)time(NULL));

    float lim1 = xavier_limit(INPUT_SIZE, HIDDEN_SIZE);
    float lim2 = xavier_limit(HIDDEN_SIZE, OUTPUT_SIZE);

    for (int i = 0; i < INPUT_SIZE; i++)
    {
        for (int j = 0; j < HIDDEN_SIZE; j++)
        {
            nn->w1[i][j] = randf() * lim1;
        }
    }

    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        nn->b1[i] = 0.0f;
    }

    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        for (int j = 0; j < OUTPUT_SIZE; j++)
        {
            nn->w2[i][j] = randf() * lim2;
        }
    }

    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        nn->b2[i] = 0.0f;
    }
}

void nn_forward(
    NeuralNetwork *nn,
    float input[INPUT_SIZE],
    float hidden[HIDDEN_SIZE],
    float output[OUTPUT_SIZE]
)
{
    for (int i = 0; i < HIDDEN_SIZE; i++)
    {
        float sum = nn->b1[i];

        for (int j = 0; j < INPUT_SIZE; j++)
        {
            sum += input[j] * nn->w1[j][i];
        }

        hidden[i] = (sum > 0.0f) ? sum : 0.0f; // ReLU
    }

    float raw[OUTPUT_SIZE];

    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        float sum = nn->b2[i];

        for (int j = 0; j < HIDDEN_SIZE; j++)
        {
            sum += hidden[j] * nn->w2[j][i];
        }

        raw[i] = sum;
    }

    softmax(raw, output, OUTPUT_SIZE);
}

void softmax(float *input, float *output, int size)
{
    float max = input[0];

    for (int i = 1; i < size; i++)
        if (input[i] > max)
            max = input[i];

    float sum = 0.0f;

    for (int i = 0; i < size; i++)
    {
        output[i] = expf(input[i] - max);
        sum += output[i];
    }

    for (int i = 0; i < size; i++)
    {
        output[i] /= sum;
    }
}

float cross_entropy_loss(float output[OUTPUT_SIZE], int label)
{
    float p = output[label];

    if (p < 1e-7f)
        p = 1e-7f;

    return -logf(p);
}

int nn_predict(float output[OUTPUT_SIZE])
{
    int best = 0;

    for (int i = 1; i < OUTPUT_SIZE; i++)
    {
        if (output[i] > output[best])
            best = i;
    }

    return best;
}

void nn_backprop(
    NeuralNetwork *nn,
    float input[INPUT_SIZE],
    float hidden[HIDDEN_SIZE],
    float output[OUTPUT_SIZE],
    int label
)
{
    float dOutput[OUTPUT_SIZE];

    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        float y = (i == label) ? 1.0f : 0.0f;
        dOutput[i] = output[i] - y;
    }

    for (int i = 0; i < OUTPUT_SIZE; i++)
    {
        nn->b2[i] -= LR * dOutput[i];

        for (int j = 0; j < HIDDEN_SIZE; j++)
        {
            nn->w2[j][i] -= LR * hidden[j] * dOutput[i];
        }
    }

    float dHidden[HIDDEN_SIZE] = {0};

    for (int j = 0; j < HIDDEN_SIZE; j++)
    {
        float sum = 0.0f;

        for (int i = 0; i < OUTPUT_SIZE; i++)
        {
            sum += nn->w2[j][i] * dOutput[i];
        }

        dHidden[j] = sum * (hidden[j] > 0.0f);
    }

    for (int j = 0; j < HIDDEN_SIZE; j++)
    {
        nn->b1[j] -= LR * dHidden[j];

        for (int i = 0; i < INPUT_SIZE; i++)
        {
            nn->w1[i][j] -= LR * input[i] * dHidden[j];
        }
    }
}