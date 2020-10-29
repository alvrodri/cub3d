/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/28 13:22:06 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_movement(t_data *data)
{
	ft_move(data);
	ft_move_sides(data);
	if (data->player.keys.right == 1)
		ft_rotate_right(data);
	if (data->player.keys.left == 1)
		ft_rotate_left(data);
}

void	ft_move(t_data *data)
{
	if (data->player.keys.w == 1)
	{
		if (data->map.map[(int)(data->player.x +
			data->player.dir_x * PLAYER_SPEED)][(int)data->player.y] == '0')
			data->player.x += data->player.dir_x * PLAYER_SPEED;
		if (data->map.map[(int)data->player.x][(int)(data->player.y +
			data->player.dir_y * PLAYER_SPEED)] == '0')
			data->player.y += data->player.dir_y * PLAYER_SPEED;
	}
	else if (data->player.keys.s == 1)
	{
		if (data->map.map[(int)(data->player.x -
			data->player.dir_x * PLAYER_SPEED)][(int)data->player.y] == '0')
			data->player.x -= data->player.dir_x * PLAYER_SPEED;
		if (data->map.map[(int)data->player.x][(int)(data->player.y -
			data->player.dir_y * PLAYER_SPEED)] == '0')
			data->player.y -= data->player.dir_y * PLAYER_SPEED;
	}
}

void	ft_move_sides(t_data *data)
{
	if (data->player.keys.d == 1)
	{
		if (data->map.map[(int)(data->player.x +
			data->player.dir_y * PLAYER_SPEED)][(int)data->player.y] == '0')
			data->player.x += data->player.dir_y * PLAYER_SPEED;
		if (data->map.map[(int)data->player.x][(int)(data->player.y -
			data->player.dir_x * PLAYER_SPEED)] == '0')
			data->player.y -= data->player.dir_x * PLAYER_SPEED;
	}
	else if (data->player.keys.a == 1)
	{
		if (data->map.map[(int)(data->player.x -
			data->player.dir_y * PLAYER_SPEED)][(int)data->player.y] == '0')
			data->player.x -= data->player.dir_y * PLAYER_SPEED;
		if (data->map.map[(int)data->player.x][(int)(data->player.y +
			data->player.dir_x * PLAYER_SPEED)] == '0')
			data->player.y += data->player.dir_x * PLAYER_SPEED;
	}
}

void	ft_rotate_left(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(ROTATION_SPEED) -
		data->player.dir_y * sin(ROTATION_SPEED);
	data->player.dir_y = old_dir_x * sin(ROTATION_SPEED) +
		data->player.dir_y * cos(ROTATION_SPEED);
	data->player.plane_x = data->player.plane_x * cos(ROTATION_SPEED)
		- data->player.plane_y * sin(ROTATION_SPEED);
	data->player.plane_y = old_plane_x * sin(ROTATION_SPEED)
		+ data->player.plane_y * cos(ROTATION_SPEED);
}

void	ft_rotate_right(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->player.dir_x;
	old_plane_x = data->player.plane_x;
	data->player.dir_x = data->player.dir_x * cos(-(ROTATION_SPEED))
		- data->player.dir_y * sin(-(ROTATION_SPEED));
	data->player.dir_y = old_dir_x * sin(-(ROTATION_SPEED))
		+ data->player.dir_y * cos(-(ROTATION_SPEED));
	data->player.plane_x = data->player.plane_x * cos(-(ROTATION_SPEED)) -
		data->player.plane_y * sin(-(ROTATION_SPEED));
	data->player.plane_y = old_plane_x * sin(-(ROTATION_SPEED)) +
		data->player.plane_y * cos(-(ROTATION_SPEED));
}
