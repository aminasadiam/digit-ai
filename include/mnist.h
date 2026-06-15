#pragma once

#define MNIST_PIXELS 784

typedef struct {
    float image[MNIST_PIXELS];
    int label;
} MnistSample;

int load_mnist_csv(
    const char *filename,
    MnistSample *samples,
    int max_samples
);
