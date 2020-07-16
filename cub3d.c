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
	data->player->x = 5;
	data->player->y = 5;
	data->player->dir = 0;
	data->player->fov = 60;
	data->player->pitch = 0;
}

int		render(t_data *vars)
{	
	t_img	img;
	t_ray	ray;
	t_wall	wall;

	img.img = mlx_new_image(vars->mlx_ptr, vars->width, vars->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
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
		ray.x = vars->player->x;
		ray.y = vars->player->y;
		ray.cos = cos(deg_to_rad(ray.dir)) / 128;
		ray.sin = sin(deg_to_rad(ray.dir)) / 128;
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
			{
				ray.cardinal = ray.sin < 0 ? 'S' : 'N';
				break ;
			}
		}
		ray.hit = 1;
		ray.distance = sqrt(pow((vars->player->x - ray.x), 2) + pow((vars->player->y - ray.y), 2)) * cos(deg_to_rad(ray.dir - vars->player->dir));
		wall.height = (vars->height / ray.distance);
		wall.start = -(vars->height / ray.distance) / 2 + vars->player->pitch + vars->height / 2;
		if (wall.start < 0)
			wall.start = 0;
		wall.end = (vars->height / ray.distance) / 2 +  vars->player->pitch + vars->height / 2;
		if (wall.end >= vars->height)
			wall.end = vars->height - 1;

		unsigned long color;
		if (ray.cardinal == 'N')
			color = 0xff0000;
		else if (ray.cardinal == 'E')
			color = 0x00ffff;
		else if (ray.cardinal == 'S')
			color = 0x0000ff;
		else if (ray.cardinal == 'W')
			color = 0xffffff;

		ft_draw_line(img, ft_create_point(x, 0), ft_create_point(x, wall.start), ft_t_rgb_to_hex(vars->textures->ceiling));
		ft_draw_line(img, ft_create_point(x, wall.start), ft_create_point(x, wall.end), color);
		ft_draw_line(img, ft_create_point(x, wall.end), ft_create_point(x, vars->height - 1), ft_t_rgb_to_hex(vars->textures->floor));

		ray.dir += vars->player->fov / vars->width;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, img.img, 0, 0);
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
	mlx_mouse_hide();
	mlx_loop_hook(vars->mlx_ptr, render, vars);
	mlx_hook(vars->mlx_win, 02, 1L << 0, ft_handle_key_press, vars);
	mlx_hook(vars->mlx_win, 03, 1L << 1, ft_handle_key_release, vars);
	mlx_loop(vars->mlx_ptr);
	return (0);
}
