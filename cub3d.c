/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:28:41 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/28 12:38:57 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <pthread.h>

void    ft_init(t_data *data)
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
	data->player->x = -1;
	data->player->y = -1;
	data->player->dir = 0;
	data->player->fov = 60;
	data->player->pitch = 0;
	data->fps = -1;
	data->shader = -1;
}

void	ft_init_textures(t_data *data)
{
	t_textures	*textures;
	
	textures = data->textures;

	textures->stone = malloc(sizeof(t_texture));
	textures->stone->img.img = mlx_png_file_to_image(data->mlx_ptr, "./textures/brick.png", &textures->stone->width, &textures->stone->height);
	textures->stone->img.addr = mlx_get_data_addr(textures->stone->img.img, &textures->stone->img.bits_per_pixel, &textures->stone->img.line_length, &textures->stone->img.endian);
}

void draw_texture(int x, int wallHeight, int texturePositionX, t_data *vars) {
    int yIncrementer = (wallHeight * 2) / vars->textures->stone->height;
    int y = vars->height / 2 - wallHeight;

    for(int i = 0; i < vars->textures->stone->height; i++) {
        ft_draw_line(vars, ft_create_point(x, y), ft_create_point(x, y + (yIncrementer + 0.5)), ((int*)vars->textures->stone->img.addr)[i * vars->textures->stone->width + texturePositionX]);
        y += yIncrementer;
    }
}

int		render(t_data *vars)
{	
	t_img	img;
	t_ray	ray;
	t_wall	wall;

	img.img = mlx_new_image(vars->mlx_ptr, vars->width, vars->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars->img = &img;
	ft_move(vars);
	ft_move_sides(vars);
	ft_mouse(vars);
	if (vars->player->keys->up == 1)
		ft_rotate(vars, 5, 1);
	if (vars->player->keys->down == 1)
		ft_rotate(vars, -5, 1);
	if (vars->player->keys->left == 1)
		ft_rotate(vars, -5, 0);
	if (vars->player->keys->right == 1)
		ft_rotate(vars, 5, 0);
	ray.dir = vars->player->dir - vars->player->fov / 2;
	for (int x = 0; x < vars->width; x++)
	{
		ft_raycast(vars, &ray);
		ft_raycast_hits(vars, &ray);
		if (ray.hit == 1)
		{
			int color = ray.cardinal == 'N' ? 0xFF0000 : (ray.cardinal == 'E' ? 0x00FFFF : (ray.cardinal == 'S' ? 0x0000FF : 0xFFFFFF));
			
			ray.distance = sqrt(pow((vars->player->x - ray.x), 2) + pow((vars->player->y - ray.y), 2)) * cos(deg_to_rad(ray.dir - vars->player->dir));
			wall.height = (vars->height / ray.distance);
			wall.start = -(vars->height / ray.distance) / 2 + vars->player->pitch + vars->height / 2;
			wall.end = (vars->height / ray.distance) / 2 +  vars->player->pitch + vars->height / 2;
			wall.hit_side = (ray.cardinal == 'N' || ray.cardinal == 'S') ? 'Y' : 'X';
			int texturePositionX = (int)(vars->textures->stone->width * (ray.x + ray.y)) % vars->textures->stone->width;
			ft_draw_line(vars, ft_create_point(x, 0), ft_create_point(x, wall.start), ft_t_rgb_to_hex(vars->textures->ceiling));
			ft_draw_line(vars, ft_create_point(x, wall.start), ft_create_point(x, wall.end), color);
			ft_draw_line(vars, ft_create_point(x, wall.end), ft_create_point(x, vars->height), ft_t_rgb_to_hex(vars->textures->floor));
		}
		ray.dir += vars->player->fov / vars->width;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, img.img, 0, 0);
	ft_fps(vars);
	return (1);
}

int	main(int args_n, char **args)
{
	t_data *vars;
	
	if (args_n != 2)
		return (ft_close(vars, 1));
	vars = malloc(sizeof(t_data));
	ft_init(vars);
	ft_parse_map(vars, args[1]);
	vars->mlx_ptr = mlx_init();
	vars->mlx_win = mlx_new_window(vars->mlx_ptr, vars->width, vars->height, "cub3d");
	ft_init_textures(vars);
	mlx_mouse_hide();
	mlx_loop_hook(vars->mlx_ptr, render, vars);
	mlx_hook(vars->mlx_win, 02, 1L << 0, ft_handle_key_press, vars);
	mlx_hook(vars->mlx_win, 03, 1L << 1, ft_handle_key_release, vars);
	mlx_loop(vars->mlx_ptr);
	return (0);
}