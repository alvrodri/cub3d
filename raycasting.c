/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 12:04:26 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/10 12:04:26 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_start_raycasting(int x, t_data *data, t_ray *ray)
{
	ray->camera_x = 2 * x / (double) data->width - 1;
	ray->dir_x = data->player->dir_x + data->player->plane_x * ray->camera_x;
	ray->dir_y = data->player->dir_y + data->player->plane_y * ray->camera_x;
	ray->map_x = (int) data->player->pos_x;
	ray->map_y = (int) data->player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void	ft_throw_ray(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player->pos_y) * ray->delta_dist_y;
	}
}

void	ft_check_hits(t_data *data, t_ray *ray, int map[24][24])
{
	int		side;

	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			side = 1;
		}
		if (map[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
	}
	if (side == 0)
		ray->wall_distance = (ray->map_x - data->player->pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_distance = (ray->map_y - data->player->pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
}