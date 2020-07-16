/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/06 12:17:48 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_collides(t_data *data, int to_x, int to_y)
{
	char	**map;

	map = data->map->map;
	if (map[to_x][to_y] != '0')
		return (1);
	return (0);
}

float rad_to_deg(float rad)
{
	return (fabs(rad) * 180 / M_PI);
}

float deg_to_rad(float rad)
{
	return (fabs(rad) * M_PI / 180);
}

void	ft_move_sides(t_data *data)
{
	float speed;
	
	speed = data->player->movement_speed;
	if (data->player->keys->d)
	{
		float x = (deg_to_rad(rad_to_deg(data->player->dir_x) + 90));
		float y = (deg_to_rad(rad_to_deg(data->player->dir_y) + 90));

		data->player->pos_x += x * speed;
		data->player->pos_y += y * speed;
	}
}

void	ft_move(t_data *data)
{
	float movement_speed;

	ft_move_sides(data);
	if (data->player->keys->w == 1 || data->player->keys->s == 1)
	{
		movement_speed = data->player->keys->w == 1 ? data->player->movement_speed : -data->player->movement_speed;
		if (!ft_collides(data, data->player->pos_x + data->player->dir_x * movement_speed, data->player->pos_y))
			data->player->pos_x += data->player->dir_x * movement_speed;
		if (!ft_collides(data, data->player->pos_x, data->player->pos_y +data->player->dir_y * movement_speed))
			data->player->pos_y += data->player->dir_y * movement_speed;
	}
}

void	ft_rotate_right(t_data *data)
{
	float old_dir_x;
	float old_plane_x;
	float rotation;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	rotation = data->player->rotation_speed;
	data->player->dir_x = data->player->dir_x * cos(rotation) -
							data->player->dir_y * sin(-rotation);
	data->player->dir_y = old_dir_x * sin(-rotation) +
						  data->player->dir_y * cos(-rotation);
	data->player->plane_x = data->player->plane_x * cos(-rotation)-
							data->player->plane_y * sin(-rotation);
	data->player->plane_y = old_plane_x * sin(-rotation) +
							data->player->plane_y * cos(-rotation);
}

void	ft_rotate_left(t_data *data)
{
	double old_dir_x;
	double old_plane_x;
	double rotation;

	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	rotation = data->player->rotation_speed;
	data->player->dir_x = data->player->dir_x * cos(rotation) -
						  data->player->dir_y * sin(rotation);
	data->player->dir_y = old_dir_x * sin(rotation) +
						  data->player->dir_y * cos(rotation);
	data->player->plane_x = data->player->plane_x * cos(rotation) -
							data->player->plane_y * sin(rotation);
	data->player->plane_y = old_plane_x * sin(rotation) +
							data->player->plane_y * cos(rotation);
}
