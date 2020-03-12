/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:25:06 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/10 18:15:33 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# define WIDTH 1024
# define HEIGHT 768

# include "./minilibx/mlx.h"
# include "./libft/libft.h"
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

typedef	struct	s_player {
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		movement_speed;
	double		rotation_speed;
	double		pitch;
	t_keys		*keys;
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

typedef struct  s_data {
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_img;
	t_player	*player;
}				t_data;

unsigned	int	ft_get_color(int x, int y, int map[24][24]);
int				ft_close(t_data *data);
int				ft_handle_key_press(int keycode, t_data *data);
int				ft_handle_key_release(int keycode, t_data *data);
void    		ft_start_raycasting(int x, t_data *data, t_ray *ray);
void			ft_throw_ray(t_data *data, t_ray *ray);
void			ft_check_hits(t_data *data, t_ray *ray, int map[24][24]);
void			ft_move_forward(t_data *data, int map[24][24]);
void			ft_move_backwards(t_data *data, int map[24][24]);
void			ft_rotate_right(t_data *data);
void			ft_rotate_left(t_data *data);
void			ft_send_instructions(t_data *data);
void			ft_draw_pixel(t_data *data, int x, int y, unsigned int color);
#endif
