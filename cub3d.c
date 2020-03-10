/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:24:33 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/10 16:10:28 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mapa[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
}

int   ft_loop(t_data *data)
{
	int x;
	
	if (data->player->keys->w == 1)
	{
		if (mapa[(int)(data->player->pos_x + data->player->dir_x)][(int)data->player->pos_y] == 0)
			data->player->pos_x += data->player->dir_x;
		if (mapa[(int)data->player->pos_y][(int)(data->player->pos_y + data->player->dir_y)] == 0)
			data->player->pos_y += data->player->dir_y;
	}
	if (data->player->keys->s == 1)
	{
		if (mapa[(int)(data->player->pos_x - data->player->dir_x)][(int)data->player->pos_y] == 0)
			data->player->pos_x -= data->player->dir_x;
		if (mapa[(int)data->player->pos_y][(int)(data->player->pos_y - data->player->dir_y)] == 0)
			data->player->pos_y -= data->player->dir_y;
	}
	if (data->player->keys->a == 1)
    {
      double oldDirX = data->player->dir_x;
      data->player->dir_x = data->player->dir_x * cos(100) - data->player->dir_y * sin(-100);
      data->player->dir_y = oldDirX * sin(-100) + data->player->dir_y * cos(-100);
      double oldPlaneX = data->player->plane_x;
      data->player->plane_x = data->player->plane_x * cos(-100) - data->player->plane_y * sin(-100);
      data->player->plane_y = oldPlaneX * sin(-100) + data->player->plane_y * cos(-100);
    }
	if (data->player->keys->d == 1)
    {
      double oldDirX = data->player->dir_x;
      data->player->dir_x = data->player->dir_x * cos(100) - data->player->dir_y * sin(100);
      data->player->dir_y = oldDirX * sin(100) + data->player->dir_y * cos(100);
      double oldPlaneX = data->player->plane_x;
      data->player->plane_x = data->player->plane_x * cos(100) - data->player->plane_y * sin(100);
      data->player->plane_y = oldPlaneX * sin(100) + data->player->plane_y * cos(100);
    }
	x = 0;
	while (x < WIDTH)
	{
		t_ray ray;

		ft_start_raycasting(x, data, &ray);
		ft_throw_ray(data, &ray);
		ft_check_hits(data, &ray);
		int draw_start = -(HEIGHT / ray.wall_distance) / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = (HEIGHT / ray.wall_distance) / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		int j = 0;
		while (j < draw_start)
		{
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, j, 0x000000);
			j++;
		}
		int i = draw_start;
		while (i < draw_end)
		{
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, i, 0x00FF00);
			i++;
		}
		j = draw_end;
		while (j < HEIGHT)
		{
			mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, j, 0x999999);
			j++;
		}
		x++;
	}
	return (1);
}

int		main(void)
{
	t_data	data;

	init(&data);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, WIDTH, HEIGHT, "cub3d");
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_handle_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_handle_key_release, &data);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop_hook(data.mlx_ptr, ft_loop, &data);
	mlx_loop(data.mlx_ptr);
}
