/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/16 18:15:22 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mouse(t_data *data)
{
	t_mouse *mouse;
	int	x_diff;
	int	y_diff;

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

void    ft_move(t_data *data, int map[24][24])
{
	double	movement_speed;

	movement_speed = data->player->current_speed;
	(data->player->keys->shift ? movement_speed *= 1.85 : 0);
	if (map[(int)(data->player->pos_x + data->player->dir_x * movement_speed)]
	[(int)data->player->pos_y] == 0)			
		data->player->pos_x += data->player->dir_x * movement_speed;
	if (map[(int)data->player->pos_x]
	[(int)(data->player->pos_y + data->player->dir_y * movement_speed)] == 0)
		data->player->pos_y += data->player->dir_y * movement_speed;
}

void	ft_rotate_right(t_data *data)
{
	double old_dir_x;
		double old_plane_x = data->player->plane_x;
	double rotation = data->player->rotation_speed;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	rotation = data->player->rotation_speed;
		data->player->dir_x = data->player->dir_x * cos(rotation) -
		data->player->dir_y * sin(-rotation);
		data->player->dir_y = old_dir_x * sin(-rotation) +
		data->player->dir_y * cos(-rotation);
		data->player->plane_x = data->player->plane_x * cos(-rotation)
		- data->player->plane_y * sin(-rotation);
		data->player->plane_y = old_plane_x * sin(-rotation) +
		data->player->plane_y * cos(-rotation);
}

void	ft_rotate_left(t_data *data)
{
	double old_dir_x = data->player->dir_x;
		double old_plane_x = data->player->plane_x;
	double rotation = data->player->rotation_speed;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	rotation = data->player->rotation_speed;
		data->player->dir_x = data->player->dir_x * cos(rotation) -
		data->player->dir_y * sin(rotation);
		data->player->dir_y = old_dir_x * sin(rotation) +
		data->player->dir_y * cos(rotation);
		data->player->plane_x = data->player->plane_x * cos(rotation)
		- data->player->plane_y * sin(rotation);
		data->player->plane_y = old_plane_x * sin(rotation) +
		data->player->plane_y * cos(rotation);
}
