/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 09:56:14 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/23 10:00:07 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned long	ft_dimmed_color(unsigned long color, float distance)
{
	int r = ((color >> 16 & 0xFF));
	int g = ((color >> 8 & 0xFF));
	int b = ((color & 0xFF));
	
	r = r - (distance / 100 * 255);
	if (r < 0)
		r = 0;
	g = g - (distance / 100 * 255);
	if (g < 0)
		g = 0;
	b = b - (distance / 100 * 255);
	if (b < 0)
		b = 0;
	return (ft_rgb_to_hex(r, g, b));
}

unsigned long   ft_negative_color(unsigned long color)
{
    return 0xffffff ^ color;
}

void			ft_shadow_shader(t_data *data)
{
	if (data->shader != -1)
	{
		for (int x = 0; x < data->width; x++)
		{
			for (int y = 0; y < data->height; y++)
			{
				((int *)data->img->addr)[y * data->width + x] = data->shader == 1 ? ft_dimmed_color(((int *)data->img->addr)[y * data->width + x], 50) : ft_negative_color(((int *)data->img->addr)[y * data->width + x]);
			}
		}
	}
}