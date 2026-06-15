#include "app.h"
#include <stdio.h>

void init_app(App *app)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
    SetTargetFPS(60);

    init_canvas(&app->canvas, WINDOW_WIDTH);
    nn_init(&app->nn);

    app->predicted = -1;

    app->dirty = 1;
    app->frame = 0;
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
        nn_forward(&app->nn, app->input, app->hidden, app->output);
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

    if (app->predicted >= 0)
    {
        char text[64];
        sprintf(text, "Prediction: %d", app->predicted);
        DrawText(text, 10, 40, 30, YELLOW);
    }

    EndDrawing();
}

void destroy_app()
{
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
