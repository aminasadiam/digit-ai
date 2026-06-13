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
    else
    {
        clear_canvas(&app->canvas);
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