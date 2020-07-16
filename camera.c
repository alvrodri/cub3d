#include "cub3d.h"

void	ft_mouse(t_data *data)
{
	t_mouse	*mouse;
	float		x_diff;
	float		y_diff;

	mouse = data->player->mouse;
	mlx_mouse_get_pos(data->mlx_win, &mouse->x, &mouse->y);
	x_diff = mouse->x - data->width / 2;
	y_diff = mouse->y - data->height / 2;
	if (x_diff)
		ft_rotate(data, x_diff, 0);
	if (y_diff)
		ft_rotate(data, -(y_diff), 1);

	mlx_mouse_move(data->mlx_win, data->width / 2, data->height / 2);
}