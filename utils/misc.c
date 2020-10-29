/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/26 10:16:20 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_close(t_data *data, int error)
{
	if (error)
		write(1, "Error\n", 6);
	mlx_mouse_show();
	if (data->mlx_ptr && data->mlx_win)
		mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(1);
	return (1);
}

float			deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

unsigned	int	ft_rgb_to_hex(int r, int g, int b)
{
	if (r < 0 || g < 0 || b < 0)
		return (0 << 16 | 0 << 8 | 0);
	return (r << 16 | g << 8 | b);
}

unsigned	int	ft_t_rgb_to_hex(int rgb[3])
{
	if (rgb[0] < 0 || rgb[1] < 0 || rgb[2] < 0)
		return (0 << 16 | 0 << 8 | 0);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}
