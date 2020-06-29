/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:25:06 by alvrodri          #+#    #+#             */
/*   Updated: 2020/06/29 12:11:47 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# define MAX_SPEED 0.005
# define MIN_SPEED -0.085
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "time.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "math.h"

typedef	struct	s_keys {
	int			w;
	int			a;
	int			s;
	int			d;
	int			up;
	int			down;
	int			shift;
}				t_keys;

typedef struct	s_mouse {
	int			x;
	int			y;
	int			last_x;
	int			last_y;
}				t_mouse;

typedef	struct	s_player {
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		movement_speed;
	double		current_speed;
	double		rotation_speed;
	double		pitch;
	t_keys		*keys;
	t_mouse		*mouse;
}				t_player;

typedef struct	s_ray {
	double		camera_x;
	double		dir_x;
	double		dir_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	double		wall_distance;
	int			step_x;
	int			step_y;
	int			map_x;
	int			map_y;
	int			hit;
}				t_ray;

typedef struct	s_map {
	char		**map;
	int			size;
	int			x;
	int			y;
	void		*image;
}				t_map;

typedef	struct s_texture {
	int			width;
	int			height;
	void		*image;
}				t_texture;

typedef struct	s_rgb {
	int			r;
	int			g;
	int			b;
}				t_rgb;

typedef struct	s_textures {
	t_rgb		*floor;
	t_rgb		*ceiling;
	t_texture	*stone;
	t_texture	*brick;
	t_texture	*player;
}				t_textures;

typedef struct  s_data {
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_img;
	int			width;
	int			height;
	t_textures	*textures;
	t_map		*map;
	t_player	*player;
}				t_data;

unsigned	int	ft_get_color(t_data *data, int x, int y, int map[24][24]);
unsigned	int	ft_rgb_to_hex(int r, int g, int b);
unsigned	int	ft_t_rgb_to_hex(t_rgb *rgb);
int				ft_close(t_data *data, int error);
int				ft_handle_key_press(int keycode, t_data *data);
int				ft_handle_key_release(int keycode, t_data *data);
void			ft_parse_map(t_data *data, char *map);
void    		ft_start_raycasting(int x, t_data *data, t_ray *ray);
void			ft_throw_ray(t_data *data, t_ray *ray);
void			ft_check_hits(t_data *data, t_ray *ray, int map[24][24]);
void			ft_move(t_data *data, int map[24][24]);
void			ft_rotate_right(t_data *data);
void			ft_rotate_left(t_data *data);
void			ft_send_instructions(t_data *data);
void			ft_draw_pixel(t_data *data, int x, int y, unsigned int color);
void			ft_draw_crosshair(t_data *data);
void			ft_mouse(t_data *data);
void			ft_accelerate(t_data *data);
void			ft_draw_minimap(t_data *data);
void			ft_draw_player(t_data *data);
#endif
