/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 10:18:28 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/28 12:11:26 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_texture(t_data *data, t_wall wall, t_ray ray, int x)
{
	float		step;
	float		tex_pos;
	int			tex_y;
	int			y;

	step = 1 * wall.texture.height / ray.line_height;
	tex_pos = (wall.draw_start - data->height / 2 + ray.line_height / 2) * step;
	y = wall.draw_start;
	while (y < wall.draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		ft_put_pixel(data, x, y, ((unsigned int *)wall.texture.img.addr)
			[wall.texture.width * tex_y + wall.texture_x]);
		y++;
	}
}

void	ft_draw_texture(t_data *data, t_wall wall, t_ray ray, int x)
{
	float	wall_x;
	int		tex_x;

	if (ray.side == 0)
		wall_x = data->player.y + ray.perp_wall_dist * ray.dir_y;
	else
		wall_x = data->player.x + ray.perp_wall_dist * ray.dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (float)wall.texture.width);
	if (ray.side == 0 && ray.dir_x > 0)
		tex_x = wall.texture.width - tex_x - 1;
	if (ray.side == 1 && ray.dir_y < 0)
		tex_x = wall.texture.width - tex_x - 1;
	wall.texture_x = tex_x;
	print_texture(data, wall, ray, x);
}
