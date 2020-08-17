/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 11:34:48 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/31 11:50:43 by alvrodri         ###   ########.fr       */
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

void ft_bresenham(t_data *data, t_point start, t_point end, unsigned long color)
{
	int m_new;
	int slope_error;

	m_new = 2 * (end.y - start.y);
	slope_error = m_new - (end.x - start.x);
	for (int x = start.x, y = start.y; x <= end.x; x++)
	{
		ft_put_pixel(data, x, y, color);
		slope_error += m_new;
		if (slope_error >= 0)
		{
			y++;
			slope_error -= 2 * (end.x - start.x);
		}
	}
}

void ft_draw_line(t_data *data, t_point start, t_point end, unsigned long color)
{
	float x;
	float y;
	int i;
	t_line line;

	line.dx = end.x - start.x;
	line.dy = end.y - start.y;	
	line.steps = abs(line.dx) > abs(line.dy) ? abs(line.dx) : abs(line.dy); 
	line.x_inc = line.dx / (float)line.steps;
	line.y_inc = line.dy / (float)line.steps;
	x = start.x; 
    y = start.y;
	i = 0;
	while (i < line.steps)
	{
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