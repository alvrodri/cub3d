/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/08/31 12:41:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move(t_data *data)
{
	float player_cos = cos(deg_to_rad(data->player->dir)) * PLAYER_SPEED;
	float player_sin = sin(deg_to_rad(data->player->dir)) * PLAYER_SPEED;
	float next_x;
	float next_y;

	if (data->player->keys->w == 1)
	{
		next_x = data->player->x + player_cos;
		next_y = data->player->y + player_sin;

		if (data->ray.distance <= 0.5)
			return ;
		if (data->map->map[(int)next_y][(int)next_x] == '0')
		{
			data->player->x += player_cos;
			data->player->y += player_sin;
		}
	}
	if (data->player->keys->s == 1)
	{
		next_x = data->player->x - player_cos;
		next_y = data->player->y - player_sin;

		if (data->map->map[(int)next_y][(int)next_x] == '0')
		{
			data->player->x -= player_cos;
			data->player->y -= player_sin;
		}
	}
}

void	ft_move_sides(t_data *data)
{
	float 	player_cos; 
	float	player_sin;
	
	if (data->player->keys->a == 1)
	{
		player_cos = cos(deg_to_rad(data->player->dir - 90)) * PLAYER_SPEED;
		player_sin = sin(deg_to_rad(data->player->dir - 90)) * PLAYER_SPEED;
		if (data->map->map[(int)(data->player->y + player_sin)]
			[(int)(data->player->x + player_cos)] != '0')
			return ;
		data->player->x += player_cos;
		data->player->y += player_sin;
	}
	else if (data->player->keys->d == 1)
	{
		player_cos = cos(deg_to_rad(data->player->dir + 90)) * PLAYER_SPEED;
		player_sin = sin(deg_to_rad(data->player->dir + 90)) * PLAYER_SPEED;
		if (data->map->map[(int)(data->player->y + player_sin)]
			[(int)(data->player->x + player_cos)] != '0')
			return ;
		data->player->x += player_cos;
		data->player->y += player_sin;
	}
}

void	ft_rotate(t_data *data, int degrees, int pitch)
{
	if (pitch)
	{
		if (data->player->pitch + degrees > 100 || data->player->pitch + degrees < -50)
			return;
		data->player->pitch += degrees;
	}
	else
	{
		if (data->player->dir - degrees < 0)
			data->player->dir = 360 + (data->player->dir - degrees);
		else if (data->player->dir + degrees > 360)
			data->player->dir = 360 - (data->player->dir - degrees);
		else
			data->player->dir += degrees;
	}
}