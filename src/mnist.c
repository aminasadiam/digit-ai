#include "mnist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_mnist_csv(
    const char *filename,
    MnistSample *samples,
    int max_samples
)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
        return 0;

    char line[20000];

    int count = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (count >= max_samples)
            break;

        char *token = strtok(line, ",");

        if (!token)
            continue;

        samples[count].label = atoi(token);

        for (int i = 0; i < MNIST_PIXELS; i++)
        {
            token = strtok(NULL, ",");

            if (!token)
                break;

            samples[count].image[i] =
                atof(token) / 255.0f;
        }

        count++;
    }

    fclose(fp);

    return count;
}
