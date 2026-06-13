#include "app.h"

void init_app(App *app)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
    SetTargetFPS(60);
    app->is_mouse_down = 0;
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
        app->is_mouse_down = 1;
    }
    else
    {
        app->is_mouse_down = 0;
    }
}

void draw_app(App *app)
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (app->is_mouse_down)
    {
        DrawText("Mouse is down!", 10, 10, 20, DARKGRAY);
    }
    else
    {
        DrawText("Mouse is up!", 10, 10, 20, DARKGRAY);
    }

    EndDrawing();
}

void destroy_app()
{
    CloseWindow();
}