/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/16 11:34:01 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_close(t_data *data, int error)
{
	if (error)
		write(1, "Error\n", 6);
	mlx_mouse_show();
	exit(1);
	return (1);
}

float		deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

unsigned	int	ft_get_color(t_data *data, int x, int y)
{
	if (data->map->map[x][y] == '1')
		return (0x999999);
	else if (data->map->map[x][y] == '2')
		return (0x624A2E);
	else if (data->map->map[x][y] == '3')
		return (0x0000FF);
	else
		return (ft_t_rgb_to_hex(data->textures->floor));
}

unsigned	int	ft_rgb_to_hex(int r, int g, int b)
{
	if (r < 0 || g < 0 || b < 0)
		return (0 << 16 | 0 << 8 | 0);
	return (r << 16 | g << 8 | b);
}

unsigned	int	ft_t_rgb_to_hex(t_rgb *rgb)
{
	if (rgb->r < 0 || rgb->g < 0 || rgb->b < 0)
		return (0 << 16 | 0 << 8 | 0);
	return (rgb->r << 16 | rgb->g << 8 | rgb->b);
}