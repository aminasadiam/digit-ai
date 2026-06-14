#include "nn.h"

float randf()
{
    return ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
}

void nn_init(NeuralNetwork *nn)
{
    for (int i = 0; i < 784; i++)
        for (int j = 0; j < 64; j++)
            nn->w1[i][j] = randf() * 0.1f;

    for (int j = 0; j < 64; j++)
        nn->b1[j] = 0;

    for (int i = 0; i < 64; i++)
        for (int k = 0; k < 10; k++)
            nn->w2[i][k] = randf() * 0.1f;

    for (int k = 0; k < 10; k++)
        nn->b2[k] = 0;
}

float relu(float x)
{
    return x > 0 ? x : 0;
}

int nn_forward(NeuralNetwork *nn, float input[784])
{
    float hidden[64];
    float output[10];

    for (int j = 0; j < 64; j++)
    {
        hidden[j] = nn->b1[j];

        for (int i = 0; i < 784; i++)
        {
            hidden[j] += input[i] * nn->w1[i][j];
        }

        hidden[j] = relu(hidden[j]);
    }

    for (int k = 0; k < 10; k++)
    {
        output[k] = nn->b2[k];

        for (int j = 0; j < 64; j++)
        {
            output[k] += hidden[j] * nn->w2[j][k];
        }
    }

    int best = 0;
    for (int k = 1; k < 10; k++)
    {
        if (output[k] > output[best])
            best = k;
    }

    return best;
}
