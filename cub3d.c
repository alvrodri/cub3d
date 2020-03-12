/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:24:33 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/10 18:43:29 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	init(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	data->player->keys = malloc(sizeof(t_keys));
	data->player->keys->w = 0;
	data->player->keys->a = 0;
	data->player->keys->s = 0;
	data->player->keys->d = 0;
	data->player->dir_x = -1;
	data->player->dir_y = 0;
	data->player->pos_x = 12;
	data->player->pos_y = 12;
	data->player->plane_x = 0;
	data->player->plane_y = 0.7;
	data->player->time = 0;
	data->player->old_time = 0;
	data->player->movement_speed = 0.015;
	data->player->rotation_speed = 0.01;
}

int   ft_loop(t_data *data)
{
	int bits_per_pixel;
	int	size_line;
	int	endian;
	int x;
	
	if (data->player->keys->w == 1)
		ft_move_forward(data, map);
	if (data->player->keys->s == 1)
		ft_move_backwards(data, map);
	if (data->player->keys->d == 1)
		ft_rotate_right(data);
	if (data->player->keys->a == 1)
		ft_rotate_left(data);
	x = 0;
	while (x < WIDTH)
	{
		t_ray ray;

		ft_start_raycasting(x, data, &ray);
		ft_throw_ray(data, &ray);
		ft_check_hits(data, &ray, map);
		int draw_start = -(HEIGHT / ray.wall_distance) / 2 + HEIGHT / 2 + (data->player->keys->space ? 100 : 0);
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = (HEIGHT / ray.wall_distance) / 2 + HEIGHT / 2 + (data->player->keys->space ? 100 : 0);
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		int j = 0;
		while (j < draw_start)
		{
			((int *)mlx_get_data_addr(data->mlx_img, &bits_per_pixel, &size_line, &endian))[j * WIDTH + x] = 0x87CEEB;
			j++;
		}
		int i = draw_start;
		while (i < draw_end)
		{
			((int *)mlx_get_data_addr(data->mlx_img, &bits_per_pixel, &size_line, &endian))[i * WIDTH + x] = ft_get_color(&ray, map);
			i++;
		}
		j = draw_end;
		while (j < HEIGHT)
		{
			((int *)mlx_get_data_addr(data->mlx_img, &bits_per_pixel, &size_line, &endian))[j * WIDTH + x] = j % 2 == 0 ? 0x008000 : 0x006600;
			j++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->mlx_img, 0, 0);
	ft_send_instructions(data);
	return (1);
}

int		main(void)
{
	t_data	data;

	
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	data.mlx_img = mlx_new_image(data.mlx_ptr, WIDTH, HEIGHT);
	init(&data);
	mlx_put_image_to_window(data.mlx_ptr, data.mlx_win, data.mlx_img, 0, 0);
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_handle_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_handle_key_release, &data);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop_hook(data.mlx_ptr, ft_loop, &data);
	mlx_loop(data.mlx_ptr);
}
