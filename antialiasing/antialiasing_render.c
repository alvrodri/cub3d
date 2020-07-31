/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing_render.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 09:05:19 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/21 10:04:47 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static	void	ft_swap(float *a, float *b)
{
	float temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static	int		ft_parse_int(float x)
{
	return	(int)x;
}

static	float	ft_parse_float(float x)
{
	if (x > 0)
		return x - ft_parse_int(x); 
    else 
		return x - (ft_parse_int(x) + 1);
}

static	float	ft_rf_parse_float(float x)
{
	return 1 - ft_parse_float(x);
}

static	void	ft_pixel(t_data *data, int x, int y, float brightness, int r, int g, int b)
{
	int a;

	a = 255 * brightness;
	if (y < 0 || y >= data->height)
		return;
	if (x < 0 || x >= data->width)
		return;
	ft_put_pixel(data->img, x, y, (a << 24 | r << 16 | g << 8 | b));
}
 
void			ft_draw_aaline(t_data *data, t_point point_a, t_point point_b, int r, int g, int b)
{
	int	steep;

	steep = fabs(point_b.y - point_a.y) > fabs(point_b.x - point_a.x);
	if (steep)
	{
		ft_swap(&point_a.x, &point_a.y);
		ft_swap(&point_b.x, &point_b.y);
	}
	if (point_a.x > point_b.x)
	{
		ft_swap(&point_a.x, &point_b.x);
		ft_swap(&point_a.y, &point_b.y);
	}
	float d_x = point_b.x - point_a.x;
	float d_y = point_b.y - point_a.y;
	float gradient = d_y / d_x;
	if (d_x == 0.0)
		gradient = 1;
	int xpxl1 = point_a.x;
	int xpxl2 = point_b.x;
	float intersect_y = point_a.y;
	if (steep)
	{
		for (int x = xpxl1 ; x <=xpxl2 ; x++) 
        { 
            ft_pixel(data, ft_parse_int(intersect_y), x, ft_rf_parse_float(intersect_y), r, g, b); 
            ft_pixel(data, ft_parse_int(intersect_y) - 1, x, ft_parse_float(intersect_y), r, g, b);
            intersect_y += gradient; 
        }
	}
	else
    { 
        for (int x = xpxl1 ; x <=xpxl2 ; x++) 
        { 
            ft_pixel(data, x, ft_parse_int(intersect_y), ft_rf_parse_float(intersect_y), r, g, b);
            ft_pixel(data, x, ft_parse_int(intersect_y) - 1, ft_parse_float(intersect_y), r, g, b);
            intersect_y += gradient; 
        } 
    } 
}