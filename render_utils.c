#include "cub3d.h"

t_point ft_create_point(float x, float y)
{
    t_point point;

    point.x = x;
    point.y = y;
    return point;
}

void    ft_draw_line(t_img img, t_point start, t_point end, unsigned long color) 
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
	while (i <= line.steps)
	{
		pixel_put(&img, x, y, color);
		x += line.x_inc;
		y += line.y_inc;
		i++;
	}
}