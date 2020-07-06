/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:24:33 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/06 11:45:19 by alvrodri         ###   ########.fr       */
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
	data->player->dir_x = -1;
	data->player->dir_y = 0;
	data->player->pos_x = 1;
	data->player->pos_y = 1;
	data->player->plane_x = 0;
	data->player->plane_y = .7;
	data->player->movement_speed = 0.1;
	data->player->current_speed = 0;
	data->player->rotation_speed = 0.075;
	data->player->pitch = 0;
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
	int x;
	
	ft_move(data);
	ft_mouse(data);
	x = 0;
	int o = 0;
	while (x < data->width)
	{
		t_ray ray;

		ft_start_raycasting(x, data, &ray);
		ft_throw_ray(data, &ray);
		ft_check_hits(data, &ray);
		int draw_start = -(data->height / ray.wall_distance) / 2 + data->player->pitch + data->height / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = (data->height / ray.wall_distance) / 2 +  data->player->pitch + data->height / 2;
		if (draw_end >= data->height)
			draw_end = data->height - 1;
		if (draw_end < 0)
			draw_end = data->height - 1;
		int j = 0;
		while (j < draw_start)
		{
			ft_draw_pixel(data, x, j, ft_t_rgb_to_hex(data->textures->ceiling));
			j++;
		}
		int i = draw_start;
		while (i < draw_end)
		{
			ft_draw_pixel(data, x, i, 0x0000ff);
			i++;
		}
		j = draw_end;
		while (j < data->height)
		{
			ft_draw_pixel(data, x, j, ft_t_rgb_to_hex(data->textures->floor));
			j++;
		}
		x++;
	}
	//ft_draw_crosshair(data);
	ft_draw_minimap(data);
	ft_draw_crosshair(data);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->textures->player->image, data->width / 1.6, data->height / 1.3);
	if (data->player->mouse->clicked)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->textures->fire->image, data->width / 2, data->height / 2.5);	
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->textures->fire->image, data->width / 3, data->height / 3.5);	
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->textures->fire->image, data->width / 4, data->height / 4.5);	
	}	
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
