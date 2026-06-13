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

void draw_canvas(Canvas *canvas, int mouse_x, int mouse_y)
{
    int cell_size = WINDOW_WIDTH / GRID_SIZE;

    int x = mouse_x / cell_size;
    int y = mouse_y / cell_size;

    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE)
    {
        canvas->pixels[y][x] = 1.0f;
    }
}

void clear_canvas(Canvas *canvas)
{
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            canvas->pixels[i][j] = 0.0f;
}

void render_canvas(Canvas *canvas)
{
    int cellSize = WINDOW_WIDTH / GRID_SIZE;

    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            Color col = canvas->pixels[y][x] > 0 ? WHITE : BLACK;

            DrawRectangle(
                x * cellSize,
                y * cellSize,
                cellSize,
                cellSize,
                col
            );
        }
    }
}