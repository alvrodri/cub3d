/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/14 19:19:22 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_close(t_data *data, int error)
{
	if (error)
		write(1, "Error\n", 6);
	exit(1);
	return (1);
}

unsigned	int	ft_get_color(int x, int y, int map[24][24])
{
	if (map[x][y] == 1)
		return (0x999999);
	else if (map[x][y] == 2)
		return (0x624A2E);
	else if (map[x][y] == 3)
		return (0x0000FF);
	else
		return (0xFFFFFF);
}

unsigned	int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	ft_draw_pixel(t_data *data, int x, int y, unsigned int color)
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	((int *)mlx_get_data_addr(data->mlx_img, &bits_per_pixel, &size_line, &endian))[y * data->width + x] = color;
}