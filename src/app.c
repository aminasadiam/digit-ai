#include "app.h"

void init_app(App *app)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
    SetTargetFPS(60);
    app->is_mouse_down = 0;
    init_canvas(&app->canvas, WINDOW_WIDTH);
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
    }
    
    if (IsKeyPressed(KEY_C))
    {
        clear_canvas(&app->canvas);
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        canvas_to_input(&app->canvas, app->input);
        // Here you would typically pass app->input to your AI model for prediction
        output_input(app); // For demonstration, we print the input to the console
    }
}

void draw_app(App *app)
{
    BeginDrawing();
    ClearBackground(BLACK);

    render_canvas(&app->canvas);
    DrawText("Draw a digit", 10, 10, 20, DARKGRAY);

    EndDrawing();
}

void destroy_app()
{
    CloseWindow();
}

void output_input(const App *app)
{
    printf("Canvas input:\n");
    for (int i = 0; i < GRID_SIZE; i++)
    {
        for (int j = 0; j < GRID_SIZE; j++)
        {
            printf("%.1f ", app->input[i * GRID_SIZE + j]);
        }
        printf("\n");
    }
}