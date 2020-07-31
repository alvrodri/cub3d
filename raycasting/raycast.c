/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 09:22:35 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/31 09:09:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    ft_raycast(t_data *data, t_ray *ray)
{
	ray->x = data->player->x;
	ray->y = data->player->y;
	ray->cos = cos(deg_to_rad(ray->dir)) / 100;
	ray->sin = sin(deg_to_rad(ray->dir)) / 100;
}

void     ft_raycast_hits(t_data *data, t_ray *ray)
{
	while (data->map->map[(int)(ray->y)][(int)(ray->x)] == '0')
	{
		ray->x += ray->cos;
		if (data->map->map[(int)(ray->y)][(int)(ray->x)] != '0')
		{
			ray->cardinal = ray->cos < 0 ? 'W' : 'E';
			ray->hit = 1;
			break ;
		}
		ray->y += ray->sin;
		if (data->map->map[(int)(ray->y)][(int)(ray->x)] != '0')
		{
			ray->cardinal = ray->sin < 0 ? 'S' : 'N';
			ray->hit = 1;
		}
	}
	ray->hit = 1;
}