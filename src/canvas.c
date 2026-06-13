#include "canvas.h"

void init_canvas(Canvas *canvas, int window_width)
{
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            canvas->pixels[i][j] = 0.0f;

    canvas->cell_size = window_width / GRID_SIZE;
}

void draw_canvas(Canvas *canvas, int mouse_x, int mouse_y)
{
    int x = mouse_x / canvas->cell_size;
    int y = mouse_y / canvas->cell_size;

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
    for (int y = 0; y < GRID_SIZE; y++)
    {
        for (int x = 0; x < GRID_SIZE; x++)
        {
            Color col = canvas->pixels[y][x] > 0 ? WHITE : BLACK;

            DrawRectangle(
                x * canvas->cell_size,
                y * canvas->cell_size,
                canvas->cell_size,
                canvas->cell_size,
                col
            );
        }
    }
}