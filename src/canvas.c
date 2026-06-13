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

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE)
            {
                canvas->pixels[ny][nx] += 0.4f;

                if (canvas->pixels[ny][nx] > 1.0f)
                    canvas->pixels[ny][nx] = 1.0f;
            }
        }
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
            float v = canvas->pixels[y][x];

            Color col = (Color){
                255 - (int)(v * 255),
                255 - (int)(v * 255),
                255 - (int)(v * 255),
                255
            };

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

void canvas_to_input(const Canvas *canvas, float *input)
{
    for (int i = 0; i < GRID_SIZE; i++)
        for (int j = 0; j < GRID_SIZE; j++)
            input[i * GRID_SIZE + j] = canvas->pixels[i][j];
}