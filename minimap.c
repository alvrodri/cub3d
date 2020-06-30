#include "cub3d.h"

static  void    ft_draw_vertical_line(t_data *data, int x, int y, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		ft_draw_pixel(data, x, y + i, 0x000000);
		i++;
	}
}

static  void    ft_draw_horizontal_line(t_data *data, int x, int y, int length)
{
	int i;

	i = 0;
	while (i < length)
	{
		ft_draw_pixel(data, x + i, y, 0x000000);
		i++;
	}
}

static void     ft_draw_square(t_data *data, int x, int y, int size, unsigned int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_draw_pixel(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

static int		ft_is_player(t_data *data, int x, int y)
{
	return ((int)data->player->pos_x) == x && ((int)data->player->pos_y) == y;
}

void	ft_draw_minimap(t_data *data)
{
	int x;
	int y;

	x = 0;
	while (x < data->map->y)
	{
		y = 0;
		while (y < data->map->x)
		{
			ft_draw_square(data, y * 7 + 4, x * 7 + 4, 7, ft_is_player(data, x, y) ? 0xFF0FF0 : ft_get_color(data, x, y));
			y++;
		}
		x++;
	}
}