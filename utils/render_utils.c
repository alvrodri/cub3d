/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 11:34:48 by alvrodri          #+#    #+#             */
/*   Updated: 2020/08/28 11:02:11 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_point ft_create_point(float x, float y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return point;
}

void    ft_draw_line(t_data *data, t_point start, t_point end, unsigned long color)
{
	float	x;
	float	y;
    int		i;

    t_line	line;
    line.dx = end.x - start.x;
    line.dy = end.y - start.y;
    line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy);
    line.x_inc = line.dx / (float)line.steps;
    line.y_inc = line.dy / (float)line.steps;
    x = start.x;
    y = start.y;
    i = 0;
    while (i <= line.steps)
    {
        //my_mlx_pixel_put(img, line.x, line.y, colour);
		ft_put_pixel(data, x, y, color);
        x += line.x_inc;
        y += line.y_inc;
        i++;
    }
}

void ft_put_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= data->width || y < 0 || y >= data->height)
		return;
	((int *)data->img->addr)[y * data->width + x] = color;
}