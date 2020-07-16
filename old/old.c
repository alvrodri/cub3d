/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:24:33 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/07 11:00:03 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *data)
{
	data->textures = malloc(sizeof(t_textures));
	data->map = malloc(sizeof(t_map));
	data->player = malloc(sizeof(t_player));
	data->player->keys = malloc(sizeof(t_keys));
	data->player->mouse = malloc(sizeof(t_mouse));
	data->player->keys->shift = 0;
	data->player->keys->w = 0;
	data->player->keys->a = 0;
	data->player->keys->s = 0;
	data->player->keys->d = 0;
	data->player->keys->up = 0;
	data->player->keys->down = 0;
	data->player->mouse->clicked = 0;
	data->player->pos_x = 1;
	data->player->pos_y = 1;
	data->player->angle = 0;
	data->player->movement_speed = 0.075;
	data->player->rotation_speed = 5;
	data->player->pitch = 0;
	data->player->fov = 60;
}

void	init_textures(t_data *data)
{
	t_textures	*textures;
	
	textures = data->textures;
	textures->stone = malloc(sizeof(t_texture));
	textures->stone->image = mlx_png_file_to_image(data->mlx_ptr, "./textures/stone.png", &textures->stone->width, &textures->stone->height);
	textures->brick = malloc(sizeof(t_texture));
	textures->brick->image = mlx_png_file_to_image(data->mlx_ptr, "./textures/brick.png", &textures->brick->width, &textures->brick->height);
	textures->player = malloc(sizeof(t_texture));
	textures->player->image = mlx_png_file_to_image(data->mlx_ptr, "./textures/gun.png", &textures->brick->width, &textures->player->height);
	textures->fire = malloc(sizeof(t_texture));
	textures->fire->image = mlx_png_file_to_image(data->mlx_ptr, "./textures/fire.png", &textures->fire->width, &textures->fire->height);
}

int   ft_loop(t_data *data)
{
	data->mlx_img = mlx_new_image(data->mlx_ptr, data->width, data->height);

	int ray_count;
	ft_move(data);
	if (data->player->keys->a == 1)
		ft_rotate_left(data);
	if (data->player->keys->d == 1)
		ft_rotate_right(data);
	ft_mouse(data);
	float ray_dir = data->player->angle - data->player->fov / 2;

	for (int x = 0; x < data->width; x++)
	{
		float ray_pos_x = data->player->pos_x;
		float ray_pos_y = data->player->pos_y;
		
		float ray_cos = cos(deg_to_rad(ray_dir)) / 128;
		float ray_sin = sin(deg_to_rad(ray_dir)) / 128;
		
		int wall_hit = 0;
		while (wall_hit == 0)
		{
			ray_pos_x += ray_cos;
			ray_pos_y += ray_sin;
			
			if (data->map->map[(int)(ray_pos_y)][(int)(ray_pos_x)] != '0')
			{
				wall_hit = 1;
			}
		}
		
		float dist_to_wall = sqrt( pow((data->player->pos_x - ray_pos_x), 2) + pow((data->player->pos_y - ray_pos_y), 2)) * cos(deg_to_rad(ray_dir - data->player->angle));
		
		float wall_height = (data->height / dist_to_wall);
			
		if (wall_height > data->height)
			wall_height = data->height;

		int y = 0;
		
		//Paint ceiling
		int wall_rest = floor((data->height - wall_height) / 2);
		while (y < wall_rest)
		{
			pixel_put(data, x, y, 0x96c3e0);
			y++;
		}
		
		//Paint wall	
		int wall_start = (int)((data->height - wall_height) / 2);
		
		y = 0;
		while (y < wall_height)
		{
			pixel_put(data, x, wall_start + y, 0x737373);
			y++;
		}

		//Paint floor
		y = 0;
		while (y < data->height - wall_rest - wall_height)
		{
			pixel_put(data, x, wall_rest + wall_height + y, 0x1b9415);
			y++;
		}
		
		ray_dir +=  data->player->fov / data->width;
	}
	ft_draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
	return (1);
}

int		main(int args_n, char **args)
{
	t_data	data;
	
	if (args_n != 2)
		return (ft_close(&data, 1));
	init(&data);
	ft_parse_map(&data, args[1]);
	data.player->mouse->last_x = data.width / 2;
	data.player->mouse->last_y = data.height / 2;
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, data.width, data.height, "cub3d");
	data.mlx_img = mlx_new_image(data.mlx_ptr, data.width, data.height);
	init_textures(&data);
	mlx_mouse_hide();
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_handle_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_handle_key_release, &data);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop_hook(data.mlx_ptr, ft_loop, &data);
	mlx_loop(data.mlx_ptr);
}
