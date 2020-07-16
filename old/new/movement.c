/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/07 12:53:30 by alvrodri         ###   ########.fr       */
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

void	ft_move(t_data *data)
{
	float player_cos = cos(deg_to_rad(data->player->angle)) * data->player->movement_speed;
	float player_sin = sin(deg_to_rad(data->player->angle)) * data->player->movement_speed;

	if (data->player->keys->w == 1)
	{
		if (!ft_collides(data, (int)data->player->pos_x + player_cos, (int)data->player->pos_y + player_sin))
		{
			data->player->pos_x += player_cos;
			data->player->pos_y += player_sin;
		}
	}
	else if (data->player->keys->a == 1)
	{
		player_cos = cos(deg_to_rad(data->player->angle + 90)) * data->player->movement_speed;
		player_sin = sin(deg_to_rad(data->player->angle + 90)) * data->player->movement_speed;

		if (!ft_collides(data, (int)data->player->pos_x - player_cos, (int)data->player->pos_y - player_sin))
		{
			data->player->pos_x -= player_cos;
			data->player->pos_y -= player_sin;
		}
	}
	else if (data->player->keys->s == 1)
	{
		if (!ft_collides(data, (int)data->player->pos_x - player_cos, (int)data->player->pos_y - player_sin))
		{
			data->player->pos_x -= player_cos;
			data->player->pos_y -= player_sin;
		}
	}
	else if (data->player->keys->d == 1)
	{
		player_cos = cos(deg_to_rad(data->player->angle - 90)) * data->player->movement_speed;
		player_sin = sin(deg_to_rad(data->player->angle - 90)) * data->player->movement_speed;

		if (!ft_collides(data, (int)data->player->pos_x - player_cos, (int)data->player->pos_y - player_sin))
		{
			data->player->pos_x -= player_cos;
			data->player->pos_y -= player_sin;
		}
	}
}

void	ft_rotate(t_data *data)
{
}
