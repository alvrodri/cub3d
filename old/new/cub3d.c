#include "cub3d.h"

#define screen_width 1280
#define screen_height 720

void	init(t_data *data)
{
	data->textures = malloc(sizeof(t_textures));
	data->map = malloc(sizeof(t_map));
	data->player = malloc(sizeof(t_player));
	data->player->keys = malloc(sizeof(t_keys));
	data->player->mouse = malloc(sizeof(t_mouse));
	data->player->keys->w = 0;
	data->player->keys->a = 0;
	data->player->keys->s = 0;
	data->player->keys->d = 0;
	data->player->keys->up = 0;
	data->player->keys->down = 0;
	data->player->pos_x = 5;
	data->player->pos_y = 5;
	data->player->angle = 0;
	data->player->fov = 60;
	data->player->movement_speed = 0.1;
	data->player->rotation_speed = 0.075;
	data->player->pitch = 0;
}

int ft_loop(t_data *data)
{	
	t_img img;
	img.img = mlx_new_image(data->mlx_ptr, screen_width, screen_height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	float ray_dir = data->player->angle - data->player->fov / 2;

	for (int x = 0; x < screen_width; x++)
	{
		ft_move(data);
		ft_rotate(data);

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
		
		float wall_height = (screen_height / dist_to_wall);
			
		if (wall_height > screen_height)
			wall_height = screen_height;

		int y = 0;
		
		//Paint ceiling
		int wall_rest = floor((screen_height - wall_height) / 2);
		while (y < wall_rest)
		{
			pixel_put(&img, x, y, ft_t_rgb_to_hex(data->textures->ceiling));
			y++;
		}
		
		//Paint wall	
		int wall_start = (int)((screen_height - wall_height) / 2);
		
		y = 0;
		while (y < wall_height)
		{
			pixel_put(&img, x, wall_start + y, 0x737373);
			y++;
		}

		//Paint floor
		y = 0;
		while (y < screen_height - wall_rest - wall_height)
		{
			pixel_put(&img, x, wall_rest + wall_height + y, ft_t_rgb_to_hex(data->textures->floor));
			y++;
		}
		
		ray_dir += data->player->fov / screen_width;
	}
	
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, img.img, 0, 0);

	return (1);
}

int	main(int args_n, char **args)
{
	t_data data;
	
	if (args_n != 2)
		return (ft_close(&data, 1));
	init(&data);
	ft_parse_map(&data, args[1]);
	data.mlx_ptr = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx_ptr, data.width, data.height, "cub3d");
	data.mlx_img = mlx_new_image(data.mlx_ptr, data.width, data.height);
	mlx_mouse_hide();
	mlx_hook(data.mlx_win, 02, 1L << 0, ft_handle_key_press, &data);
	mlx_hook(data.mlx_win, 03, 1L << 1, ft_handle_key_release, &data);
	mlx_hook(data.mlx_win, 17, 1L << 0, ft_close, &data);
	mlx_loop_hook(data.mlx_ptr, ft_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}
