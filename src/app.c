#include "app.h"
#include "mnist.h"
#include <stdio.h>
#include <stdlib.h>

void init_app(App *app)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
    SetTargetFPS(60);

    init_canvas(&app->canvas, WINDOW_WIDTH);
    nn_init(&app->nn);

    app->train_set =
        malloc(sizeof(MnistSample) * MAX_TRAIN_SAMPLES);

    if (!app->train_set)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    app->train_count =
        load_mnist_csv("./assets/mnist_train.csv",
                        app->train_set,
                        MAX_TRAIN_SAMPLES);

    printf("Loaded %d samples\n", app->train_count);

    app->test_set =
        malloc(sizeof(MnistSample) * MAX_TEST_SAMPLES);

    if (!app->test_set)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    app->test_count =
        load_mnist_csv("./assets/mnist_test.csv",
                        app->test_set,
                        MAX_TEST_SAMPLES);

    printf("Loaded %d samples\n", app->test_count);

    app->predicted = -1;
    app->dirty = 1;
    app->frame = 0;

    app->training = 0;
    app->epoch = 0;
}

void run_app(App *app)
{
    while (!WindowShouldClose())
    {
        update_app(app);
        draw_app(app);
    }
}

void update_app(App *app)
{
    if (IsKeyPressed(KEY_T))
    {
        app->training = 1;
        printf("🚀 Training started...\n");
    }

    if (app->training)
    {
        train_one_epoch(app);
        evaluate(app);

        app->epoch++;

        if (app->epoch >= 20)
        {
            printf("⛔ Max epochs reached\n");
            app->training = 0;
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 m = GetMousePosition();
        draw_canvas(&app->canvas, (int)m.x, (int)m.y);
        app->dirty = 1;
    }

    if (IsKeyPressed(KEY_C))
    {
        clear_canvas(&app->canvas);
        app->dirty = 1;
        app->predicted = -1;
    }

    app->frame++;

    if (app->dirty && app->frame % 2 == 0)
    {
        canvas_to_input(&app->canvas, app->input);

        nn_forward(&app->nn,
                   app->input,
                   app->hidden,
                   app->output);

        app->predicted = nn_predict(app->output);

        app->dirty = 0;
    }
}

void draw_app(App *app)
{
    BeginDrawing();
    ClearBackground(BLACK);

    render_canvas(&app->canvas);

    DrawText("Draw a digit", 10, 10, 20, GRAY);

    draw_input_debug(app);
    draw_output(app);

    if (app->training)
    {
        DrawText("TRAINING...", 10, 70, 20, RED);
    }

    if (app->predicted >= 0)
    {
        char text[64];
        sprintf(text, "Prediction: %d", app->predicted);
        DrawText(text, 10, 40, 30, YELLOW);
    }

    EndDrawing();
}

void destroy_app(App *app)
{
    free(app->train_set);
    free(app->test_set);
    CloseWindow();
}

void draw_output(const App *app)
{
    for (int i = 0; i < 10; i++)
    {
        char text[64];
        sprintf(text, "%d: %.2f", i, app->output[i]);
        DrawText(text, 10, 100 + i * 20, 20, WHITE);
    }
}

void draw_input_debug(const App *app)
{
    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            float v = app->input[y * GRID_SIZE + x];

            Color c = (Color){
                (unsigned char)(v * 255),
                (unsigned char)(v * 255),
                (unsigned char)(v * 255),
                255
            };

            DrawRectangle(
                10 + x * 10,
                400 + y * 10,
                10,
                10,
                c
            );
        }
    }
}

void train_one_epoch(App *app)
{
    float total_loss = 0.0f;
    int correct = 0;

    for (int i = 0; i < app->train_count; i++)
    {
        MnistSample *sample = &app->train_set[i];

        nn_forward(
            &app->nn,
            sample->image,
            app->hidden,
            app->output
        );

        total_loss += cross_entropy_loss(
            app->output,
            sample->label
        );

        int predicted = nn_predict(app->output);

        if (predicted == sample->label)
            correct++;

        nn_backprop(
            &app->nn,
            sample->image,
            app->hidden,
            app->output,
            sample->label
        );
    }

    float accuracy =
        (float)correct * 100.0f /
        (float)app->train_count;

    printf(
        "loss = %.4f | accuracy = %.2f%%\n",
        total_loss / app->train_count,
        accuracy
    );
}

void evaluate(App *app)
{
    int correct = 0;

    for (int i = 0; i < app->test_count; i++)
    {
        MnistSample *s = &app->test_set[i];

        nn_forward(
            &app->nn,
            s->image,
            app->hidden,
            app->output
        );

        if (nn_predict(app->output) == s->label)
            correct++;
    }

    printf(
        "TEST accuracy = %.2f%%\n",
        100.0f * correct / app->test_count
    );
}