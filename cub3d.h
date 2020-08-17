/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:25:06 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/31 11:50:09 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "time.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "math.h"

# define PLAYER_SPEED 0.2

typedef	struct	s_keys {
	int			w;
	int			a;
	int			s;
	int			d;
	int			up;
	int			left;
	int			right;
	int			down;
	int			shift;
}				t_keys;

typedef struct	s_mouse {
	int			x;
	int			y;
	int			last_x;
	int			last_y;
	int			clicked;
}				t_mouse;

typedef struct	s_img {
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef	struct	s_point {
	float		x;
	float		y;
}				t_point;

typedef struct s_line {
	int dx;
	int dy;
	int steps;
	float x_inc;
	float y_inc;
} 				t_line;

typedef struct	s_wall {
	int			start;
	int			end;
	int			hit_side;
	float		height;
}				t_wall;

typedef	struct	s_player {
	float		x;
	float		y;
	float		dir;
	float		fov;
	float		pitch;
	t_keys		*keys;
	t_mouse		*mouse;
}				t_player;

typedef struct	s_ray {
	float		x;
	float		y;
	float		sin;
	float		cos;
	float		distance;
	float		dir;
	int			hit;
	int			cardinal;
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
	t_img		img;
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
	t_texture	*sprite;
	t_texture	*fire;
}				t_textures;

typedef struct  s_data {
	void		*mlx_ptr;
	void		*mlx_win;
	int			width;
	int			height;
	int			fps;
	int			shader;
	t_img		*img;
	t_textures	*textures;
	t_map		*map;
	t_player	*player;
}				t_data;

unsigned	int	ft_get_color(t_data *data, int x, int y);
unsigned	int	ft_rgb_to_hex(int r, int g, int b);
unsigned	int	ft_t_rgb_to_hex(t_rgb *rgb);
float			deg_to_rad(float deg);
int				ft_close(t_data *data, int error);
int				ft_handle_key_press(int keycode, t_data *data);
int				ft_handle_key_release(int keycode, t_data *data);
int				ft_handle_button_press(int keycode, t_data *data);
int				ft_handle_button_release(int keycode, t_data *data);
void			ft_parse_map(t_data *data, char *map);
void    		ft_raycast(t_data *data, t_ray *ray);
void    		ft_raycast_hits(t_data *data, t_ray *ray);
void			ft_move(t_data *data);
void			ft_rotate_right(t_data *data);
void			ft_rotate_left(t_data *data);
void			ft_send_instructions(t_data *data);
void			ft_draw_pixel(t_data *data, int x, int y, unsigned int color);
void			ft_draw_crosshair(t_data *data);
void			ft_mouse(t_data *data);
void			ft_accelerate(t_data *data);
void			ft_draw_minimap(t_data *data);
void			ft_draw_player(t_data *data);
void  		 	ft_put_pixel(t_data *data, int x, int y, int color);
void			ft_rotate(t_data *data, int degrees, int pitch);
void			ft_move_sides(t_data *data);
void    		ft_draw_line(t_data *data, t_point start, t_point end, unsigned long color);
void    		ft_set_spawn(t_data *data);
void			ft_fps(t_data *data);
t_point 		ft_create_point(float x, float y);
unsigned long	ft_dimmed_color(unsigned long color, float distance);
void			ft_draw_aaline(t_data *data, t_point point_a, t_point point_b, int r, int g, int b);
void			ft_shadow_shader(t_data *data);
void 			ft_bresenham(t_data *data, t_point start, t_point end, unsigned long color);
#endif
