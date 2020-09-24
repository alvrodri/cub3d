/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 10:28:41 by alvrodri          #+#    #+#             */
/*   Updated: 2020/09/24 10:59:47 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    ft_init(t_data *data)
{
	data->mlx_ptr = 0;
	data->player.keys.shift = 0;
	data->player.keys.w = 0;
	data->player.keys.a = 0;
	data->player.keys.s = 0;
	data->player.keys.d = 0;
	data->player.keys.up = 0;
	data->player.keys.down = 0;
	data->player.x = -1;
	data->player.y = -1;
	data->player.dir = 0;
	data->player.fov = 60;
	data->player.pitch = 0;
	data->ray.distance = 0;
}

void	ft_init_textures(t_data *data)
{
	ft_init_texture(data, &data->textures.north,
		"./textures/mud_texture.xpm");
	ft_init_texture(data, &data->textures.south,
		"./textures/stone_texture.xpm");
	ft_init_texture(data, &data->textures.east,
		"./textures/white_texture.xpm");
	ft_init_texture(data, &data->textures.west,
		"./textures/brick_texture.xpm");
	ft_init_texture(data, &data->sprite.texture,
		"./textures/barrel.xpm");
}

void	ft_sprites(t_data *data, t_sprite *sprite)
{
	printf("\n####################\n");
	sprite->map_x = (int)sprite->map_x + .5;
	sprite->map_y = (int)sprite->map_y + .5;
	printf("map_x = %f, map_y = %f\n", sprite->map_x, sprite->map_y);
	sprite->distance = sqrt(pow(sprite->map_x - data->player.x, 2) + pow(sprite->map_y - data->player.y, 2));
	printf("distance = %f\n", sprite->distance);
	sprite->draw_height = (int)(data->height / 2 / sprite->distance);
	if ((data->player.dir - data->player.fov / 2) < 0)
        sprite->angle0 = 360 + (data->player.dir - data->player.fov / 2);
    else
        sprite->angle0 = data->player.dir - data->player.fov / 2;
	sprite->angle1 -= sprite->angle0;
	sprite->angle2 -= sprite->angle0;
	sprite->angle = (sprite->angle1 + sprite->angle2) / 2;
	printf("after | angle0 = %f\n", sprite->angle0);
	printf("after | angle1 = %f\n", sprite->angle1);
	printf("after | angle2 = %f\n", sprite->angle2);
	printf("after | angle = %f\n\n", sprite->angle);
	sprite->screen_x = data->width / data->player.fov * sprite->angle;
	sprite->screen_y = data->height / 2;
	sprite->draw_width = (sprite->texture.width * sprite->draw_height / sprite->texture.height);
	printf("texture:\n");
	printf("   width: %d\n", sprite->texture.width);
	printf("   height: %d\n", sprite->texture.height);
	printf("draw_height = %f\n", sprite->draw_height);
	printf("draw_width = %f\n", sprite->draw_width);
	int i = sprite->screen_x - (sprite->draw_width / 2);
    while (i < sprite->screen_x + (sprite->draw_width / 2))
    {
        ft_draw_line(data, ft_create_point(i, sprite->screen_y - sprite->draw_height / 2), ft_create_point(i, sprite->screen_y + sprite->draw_height / 2), 0xff0022);
        i++;
    }
	printf("####################\n");
}

int		render(t_data *data)
{	
	t_ray		ray;
	t_wall		wall;
	t_texture	texture;
	t_sprite	sprite;
	int			barrel = 0;

	ft_movement(data);
	ray.dir = data->player.dir - data->player.fov / 2;
	for (int x = 0; x < data->width; x++)
	{
		ray.x = data->player.x;
		ray.y = data->player.y;
		ray.cos = cos(ray.dir * M_PI / 180) / 128;
		ray.sin = sin(ray.dir * M_PI / 180) / 128;
		ft_check_walls(data, &ray);
		ft_calculate_walls(data, &wall, &ray);
		sprite.hit = 0;
		sprite.ray_x = data->player.x;
		sprite.ray_y = data->player.y;
		while (sprite.hit != '2' && sprite.hit != '1')
		{
			sprite.ray_x += ray.cos;
			sprite.hit = data->map.map[(int)sprite.ray_y][(int)sprite.ray_x];
			if (sprite.hit == '2')
			{
				if (barrel == 0)
				{
					sprite.map_x = (int)sprite.ray_x;
					sprite.map_y = (int)sprite.ray_y;
					sprite.angle1 = ray.dir;
					barrel = 1;
				}
				else
					sprite.angle2 = ray.dir;
				break ;
			}
			sprite.ray_y += ray.sin;
			sprite.hit = data->map.map[(int)sprite.ray_y][(int)sprite.ray_x];
			if (sprite.hit == '2')
			{
				if (barrel == 0)
				{
					sprite.map_x = (int)sprite.ray_x;
					sprite.map_y = (int)sprite.ray_y;
					sprite.angle1 = ray.dir;
					barrel = 1;
				}
				else
					sprite.angle2 = ray.dir;
				break ;
			}
		}
		ft_select_texture(data, &ray, &texture);
		wall.texture_x = (int)(fmod(texture.width * (ray.x + ray.y), texture.width));
		ft_draw_line(data, ft_create_point(x, 0), ft_create_point(x, data->height / 2 - wall.height), ft_t_rgb_to_hex(data->textures.ceiling));
		ft_draw_texture(data, wall, texture, x);
		ft_draw_line(data, ft_create_point(x, data->height / 2 + wall.height), ft_create_point(x, data->height), ft_t_rgb_to_hex(data->textures.floor));
		
		ray.dir += data->player.fov / data->width;
		if (x == data->width / 2)
			data->ray = ray;
	}
	sprite.texture = data->sprite.texture;
	ft_sprites(data, &sprite);
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img.img, 0, 0);
	ft_fps(data);
	return (1);
}

int	main(int args_n, char **args)
{
	t_data *data;
	
	if (args_n != 2)
		return (ft_close(data, 1));
	data = malloc(sizeof(t_data));
	ft_init(data);
	ft_parse_map(data, args[1]);
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, data->width, data->height, "cub3d");
	ft_init_textures(data);
	data->img.img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = (unsigned int *)mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
	mlx_loop_hook(data->mlx_ptr, render, data);
	mlx_hook(data->mlx_win, 02, 1L << 0, ft_handle_key_press, data);
	mlx_hook(data->mlx_win, 03, 1L << 1, ft_handle_key_release, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	return (0);
}