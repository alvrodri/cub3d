/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:08:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/26 10:05:37 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_sprite_distance(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->sprites_n)
	{
		data->sprites[i].distance = ((data->player.x - data->sprites[i].map_x) *
			(data->player.x - data->sprites[i].map_x) +
				(data->player.y - data->sprites[i].map_y) *
					(data->player.y - data->sprites[i].map_y));
		i++;
	}
	sort_sprites(data);
}

void	print_sprite(t_data *data, int i, int stripe, int y)
{
	data->sprites[i].d = (y) * 256 - data->height * 128 +
		data->sprites[i].sprite_height * 128;
	data->sprites[i].tex_y = ((data->sprites[i].d *
		data->textures.sprite.height) / data->sprites[i].sprite_height) / 256;
	data->sprites[i].color = ((unsigned int*)data->textures.sprite.img.addr)
	[data->textures.sprite.width * data->sprites[i].tex_y +
		data->sprites[i].tex_x];
	if ((data->sprites[i].color & 0x00FFFFFF) != 0)
		ft_put_pixel(data, stripe, y, data->sprites[i].color);
}

void	draw_sprite(t_data *data, int i)
{
	int	stripe;
	int y;

	stripe = data->sprites[i].draw_start_x;
	while (stripe < data->sprites[i].draw_end_x)
	{
		data->sprites[i].tex_x = (int)(256 * (stripe -
			(-data->sprites[i].sprite_width / 2 +
				data->sprites[i].sprite_screen_x))
					* data->textures.sprite.width /
						data->sprites[i].sprite_width) / 256;
		if (data->sprites[i].transform_y > 0 && stripe > 0 && stripe <
			data->width && data->sprites[i].transform_y <
				data->zbuffer[stripe])
		{
			y = data->sprites[i].draw_start_y;
			while (y < data->sprites[i].draw_end_y)
			{
				print_sprite(data, i, stripe, y);
				y++;
			}
		}
		stripe++;
	}
}

void	calculate_sprite_screen(t_data *data, int i)
{
	data->sprites[i].sprite_screen_x = (int)((data->width / 2) *
		(1 + data->sprites[i].transform_x / data->sprites[i].transform_y));
	data->sprites[i].sprite_height = abs((int)(data->height /
		data->sprites[i].transform_y));
	data->sprites[i].draw_start_y = -data->sprites[i].sprite_height /
		2 + data->height / 2;
	if (data->sprites[i].draw_start_y < 0)
		data->sprites[i].draw_start_y = 0;
	data->sprites[i].draw_end_y = data->sprites[i].sprite_height /
		2 + data->height / 2;
	if (data->sprites[i].draw_end_y >= data->height)
		data->sprites[i].draw_end_y = data->height - 1;
	data->sprites[i].sprite_width = abs((int)(data->height /
		(data->sprites[i].transform_y)));
	data->sprites[i].draw_start_x = -data->sprites[i].sprite_width /
		2 + data->sprites[i].sprite_screen_x;
	if (data->sprites[i].draw_start_x < 0)
		data->sprites[i].draw_start_x = 0;
	data->sprites[i].draw_end_x = data->sprites[i].sprite_width /
		2 + data->sprites[i].sprite_screen_x;
	if (data->sprites[i].draw_end_x >= data->width)
		data->sprites[i].draw_end_x = data->width - 1;
	draw_sprite(data, i);
}

void	calculate_sprite_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->sprites_n)
	{
		data->sprites[i].calc_x = data->sprites[i].map_x - data->player.x;
		data->sprites[i].calc_y = data->sprites[i].map_y - data->player.y;
		data->sprites[i].inv_det = 1.0 / (data->player.plane_x *
			data->player.dir_y - data->player.dir_x * data->player.plane_y);
		data->sprites[i].transform_x = data->sprites[i].inv_det *
			(data->player.dir_y * data->sprites[i].calc_x - data->player.dir_x *
				data->sprites[i].calc_y);
		data->sprites[i].transform_y = data->sprites[i].inv_det *
			(-data->player.plane_y * data->sprites[i].calc_x +
				data->player.plane_x * data->sprites[i].calc_y);
		calculate_sprite_screen(data, i);
		i++;
	}
}
