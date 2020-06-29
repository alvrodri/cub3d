#include "cub3d.h"

void	ft_mouse(t_data *data)
{
	t_mouse	*mouse;
	int		x_diff;
	int		y_diff;

	mouse = data->player->mouse;
	mlx_mouse_get_pos(data->mlx_win, &mouse->x, &mouse->y);
	x_diff = mouse->x - mouse->last_x;
	y_diff = mouse->y - mouse->last_y;
	if (x_diff)
		x_diff > 0 ? ft_rotate_right(data) : ft_rotate_left(data);
	if (y_diff < 0)
	{
		if (data->player->pitch + 10 <= 500)
			data->player->pitch += 10;
	}
	else if (y_diff > 0)
	{
		if (data->player->pitch - 10 >= -300)
			data->player->pitch -= 10;
	}
	if (x_diff || y_diff)
		mlx_mouse_move(data->mlx_win, mouse->last_x, mouse->last_y);
}