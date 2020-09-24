/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 09:48:00 by alvrodri          #+#    #+#             */
/*   Updated: 2020/09/11 12:02:20 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_calculate_ray(t_data *data, t_ray *ray)
{
	ray->x = data->player.x;
	ray->y = data->player.y;
	ray->cos = cos(ray->dir * M_PI / 180) / 128;
	ray->sin = sin(ray->dir * M_PI / 180) / 128;
}

void	ft_check_walls(t_data *data, t_ray *ray)
{
	int	wall;
	
	wall = '0';
	while (wall == '0' || wall == '2')
	{
		ray->x += ray->cos;
		wall = data->map.map[(int)(ray->y)][(int)(ray->x)];
		if (wall != '0' && wall != '2')
		{
			ray->cardinal = ray->cos < 0 ? 'W' : 'E';
			break;
		}
		ray->y += ray->sin;
		wall = data->map.map[(int)(ray->y)][(int)(ray->x)];
		if (wall != '0' && wall != '2')
			ray->cardinal = ray->sin < 0 ? 'S' : 'N';
	}
}

void	ft_select_texture(t_data *data, t_ray *ray, t_texture *texture)
{
	if (ray->cardinal == 'N')
		*texture = data->textures.north;
	else if (ray->cardinal == 'S')
		*texture = data->textures.south;
	else if (ray->cardinal == 'E')
		*texture = data->textures.east;
	else
		*texture = data->textures.west;
}

void	ft_calculate_walls(t_data *data, t_wall *wall, t_ray *ray)
{
	ray->distance = sqrt(pow(data->player.x - ray->x, 2) + pow(data->player.y - ray->y, 2));
	ray->distance = ray->distance * cos((ray->dir - data->player.dir) * M_PI / 180);
	wall->height = (int)(data->height / 2 / ray->distance);
	wall->hit_side = (ray->cardinal == 'N' || ray->cardinal == 'S') ? 'Y' : 'X';
}