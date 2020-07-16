#include "cub3d.h"

static  void    ft_draw_vertical_line(t_data *data, int x, int y, int length)
{
    int i;

    i = 0;
    while (i < length)
    {
        ft_draw_pixel(data, x, y + i, 0xFF0000);
        i++;
    }
}

static  void    ft_draw_horizontal_line(t_data *data, int x, int y, int length)
{
    int i;

    i = 0;
    while (i < length)
    {
        ft_draw_pixel(data, x + i, y, 0xFF0000);
        i++;
    }
}

void    ft_draw_crosshair(t_data *data)
{
    ft_draw_horizontal_line(data, data->width / 2 + 3, data->height / 2 - 3, 6);
    ft_draw_vertical_line(data, data->width / 2, data->height / 2, 6);
    ft_draw_vertical_line(data, data->width / 2, data->height / 2 - 12, 6);
    ft_draw_horizontal_line(data, data->width / 2 - 8, data->height / 2 - 3, 6);
}