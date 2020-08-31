/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:28:41 by alvrodri          #+#    #+#             */
/*   Updated: 2020/08/31 13:27:48 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	data->ray.distance = 0;
}

void	ft_init_textures(t_data *data)
{
	t_textures	*textures;
	
	textures = data->textures;

	textures->north = malloc(sizeof(t_texture));
	textures->north->img.img = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/stone_texture.xpm", &textures->north->width, &textures->north->height);
	textures->north->img.addr = (unsigned int*) mlx_get_data_addr(textures->north->img.img, &textures->north->img.bits_per_pixel, &textures->north->img.line_length, &textures->north->img.endian);
	
	textures->south = malloc(sizeof(t_texture));
	textures->south->img.img = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/mud_texture.xpm", &textures->south->width, &textures->south->height);
	textures->south->img.addr = (unsigned int*) mlx_get_data_addr(textures->south->img.img, &textures->south->img.bits_per_pixel, &textures->south->img.line_length, &textures->south->img.endian);
	
	textures->east = malloc(sizeof(t_texture));
	textures->east->img.img = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/white_texture.xpm", &textures->east->width, &textures->east->height);
	textures->east->img.addr = (unsigned int*) mlx_get_data_addr(textures->east->img.img, &textures->east->img.bits_per_pixel, &textures->east->img.line_length, &textures->east->img.endian);

	textures->west = malloc(sizeof(t_texture));
	textures->west->img.img = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/brick_texture.xpm", &textures->west->width, &textures->west->height);
	textures->west->img.addr = (unsigned int*) mlx_get_data_addr(textures->west->img.img, &textures->west->img.bits_per_pixel, &textures->west->img.line_length, &textures->west->img.endian);
}

void	ft_draw_texture(t_data *data, t_wall wall, t_texture texture, int x) {
	float y_increment = (wall.height * 2) / texture.height;
    float y = data->height / 2 - wall.height;

	for (int i = 0; i < texture.height; i++)
	{
		ft_draw_line(data, ft_create_point(x, y), ft_create_point(x, y + y_increment),
			texture.img.addr[i * texture.width + wall.texture_x]);
		y += y_increment;
	}
}

int		render(t_data *vars)
{	
	t_img	img;
	t_ray	ray;
	t_wall	wall;

	img.img = mlx_new_image(vars->mlx_ptr, vars->width, vars->height);
	img.addr = (unsigned int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	vars->img = &img;
	ft_move(vars);
	ft_move_sides(vars);
//	ft_mouse(vars);
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
		ray.x = vars->player->x;
		ray.y = vars->player->y;
		ray.cos = cos(ray.dir * M_PI / 180) / 128;
		ray.sin = sin(ray.dir * M_PI / 180) / 128;
		while (vars->map->map[(int)(ray.y)][(int)(ray.x)] == '0')
		{
			ray.x += ray.cos;
			if (vars->map->map[(int)(ray.y)][(int)(ray.x)] != '0')
			{
				ray.cardinal = ray.cos < 0 ? 'W' : 'E';
				break ;
			}
			ray.y += ray.sin;
			if (vars->map->map[(int)(ray.y)][(int)(ray.x)] != '0')
				ray.cardinal = ray.sin < 0 ? 'S' : 'N';
		}
		ray.distance = sqrt(pow(vars->player->x - ray.x, 2) + pow(vars->player->y - ray.y, 2));
		ray.distance = ray.distance * cos((ray.dir - vars->player->dir) * M_PI / 180);
		wall.height = (int)(vars->height / 2 / ray.distance);
		wall.hit_side = (ray.cardinal == 'N' || ray.cardinal == 'S') ? 'Y' : 'X';

		t_texture *texture;
		if (ray.cardinal == 'N')
			texture = vars->textures->north;
		else if (ray.cardinal == 'S')
			texture = vars->textures->south;
		else if (ray.cardinal == 'E')
			texture = vars->textures->east;
		else
			texture = vars->textures->west;

		wall.texture_x = (int)(fmod(texture->width * (ray.x + ray.y), texture->width));

		ft_draw_line(vars, ft_create_point(x, 0), ft_create_point(x, vars->height / 2 - wall.height), ft_t_rgb_to_hex(vars->textures->ceiling));
		ft_draw_texture(vars, wall, *texture, x);
		ft_draw_line(vars, ft_create_point(x, vars->height / 2 + wall.height), ft_create_point(x, vars->height), ft_t_rgb_to_hex(vars->textures->floor));

		ray.dir += vars->player->fov / vars->width;
		if (x == vars->width / 2)
			vars->ray = ray;
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