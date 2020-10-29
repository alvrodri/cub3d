/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:25:06 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/29 12:00:13 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "fcntl.h"
# include "unistd.h"
# include "stdlib.h"
# include "math.h"

# define PLAYER_SPEED 0.2
# define ROTATION_SPEED 0.1

typedef	struct				s_keys {
	int						w;
	int						a;
	int						s;
	int						d;
	int						up;
	int						left;
	int						right;
	int						down;
	int						shift;
}							t_keys;

typedef struct				s_mouse {
	int						x;
	int						y;
	int						last_x;
	int						last_y;
	int						clicked;
}							t_mouse;

typedef struct				s_img {
	void					*img;
	unsigned int			*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_img;

typedef	struct				s_point {
	float					x;
	float					y;
}							t_point;

typedef struct				s_line {
	int						dx;
	int						dy;
	int						steps;
	float					x_inc;
	float					y_inc;
}							t_line;

typedef	struct				s_player {
	float					x;
	float					y;
	float					dir_x;
	float					dir_y;
	float					plane_x;
	float					plane_y;
	float					fov;
	float					pitch;
	t_keys					keys;
	t_mouse					mouse;
}							t_player;

typedef struct				s_ray {
	int						hit;
	int						map_x;
	int						map_y;
	int						side;
	int						step_x;
	int						step_y;
	float					dir_x;
	float					dir_y;
	float					delta_dist_x;
	float					delta_dist_y;
	float					side_dist_x;
	float					side_dist_y;
	float					perp_wall_dist;
	float					line_height;
}							t_ray;

typedef struct				s_map {
	char					**map;
	int						size;
	int						width;
	int						height;
	int						empty_line;
	int						started;
	void					*image;
}							t_map;

typedef	struct				s_texture {
	int						width;
	int						height;
	char					*path;
	t_img					img;
}							t_texture;

typedef struct				s_rgb {
	int						r;
	int						g;
	int						b;
}							t_rgb;

typedef struct				s_sprite {
	float					map_x;
	float					map_y;
	float					calc_x;
	float					calc_y;
	float					distance;
	float					inv_det;
	float					transform_x;
	float					transform_y;
	int						sprite_screen_x;
	int						sprite_height;
	int						draw_start_y;
	int						draw_end_y;
	int						sprite_width;
	int						draw_start_x;
	int						draw_end_x;
	int						tex_x;
	int						tex_y;
	int						d;
	unsigned	int			color;
	t_texture				texture;
}							t_sprite;

typedef struct				s_textures {
	int						floor[3];
	int						ceiling[3];
	t_texture				sprite;
	t_texture				north;
	t_texture				east;
	t_texture				south;
	t_texture				west;
}							t_textures;

typedef struct				s_wall {
	t_texture				texture;
	int						texture_x;
	int						x;
	float					draw_start;
	float					draw_end;
}							t_wall;

typedef	struct				s_bmp_header {
	unsigned		int		size[2];
	unsigned		short	resv1;
	unsigned		short	resv2;
	unsigned		int		offset;
}							t_bmp_header;

typedef struct				s_bmp_info_header {
	unsigned	int			headersize;
	unsigned	int			width;
	unsigned	int			height;
	unsigned	short		planes;
	unsigned	short		bpp;
	unsigned	int			compress;
	unsigned	int			imgsize;
	unsigned	int			bpmx;
	unsigned	int			bpmy;
	unsigned	int			colors;
	unsigned	int			imxtcolors;
}							t_bmp_info_header;

typedef struct				s_data {
	void					*mlx_ptr;
	void					*mlx_win;
	int						width;
	int						height;
	int						fps;
	int						shader;
	int						sprites_n;
	int						screenshot;
	float					*zbuffer;
	t_player				player;
	t_img					img;
	t_textures				textures;
	t_map					map;
	t_ray					ray;
	t_sprite				*sprites;
}							t_data;

unsigned	int				ft_t_rgb_to_hex(int rgb[3]);
float						deg_to_rad(float deg);
int							ft_close(t_data *data, int error);
void						ft_put_pixel(t_data *data, int x, int y,
							int color);
int							ft_handle_key_press(int keycode, t_data *data);
int							ft_handle_key_release(int keycode, t_data *data);
int							ft_handle_button_press(int keycode, t_data *data);
int							ft_handle_button_release(int keycode, t_data *data);
void						ft_move(t_data *data);
void						ft_rotate_right(t_data *data);
void						ft_rotate_left(t_data *data);
void						ft_send_instructions(t_data *data);
int							read_file(t_data *vars, int args_n, char **args);
int							empty_end_of_line(char *str);
int							parse_resolution_line(t_data *vars, char *str);
int							parse_texture_line(t_data
							*vars, int type, char *str);
int							parse_color_line(t_data *vars, int type, char *str);
int							check_variables(t_data *vars);
int							count_map_size(t_data *vars, char *str);
int							check_sprites_amount(t_data *data);
int							check_player_pos(t_data *vars, int y, char *str);
int							parse_map(t_data *vars, int fd);
void						initialize_vars(t_data *vars);
void						flood_fill(t_data *vars, int x,
							int y, int prev_color);
void						ft_draw_player(t_data *data);
void						ft_move_sides(t_data *data);
void						ft_draw_line(t_data *data, t_point start,
							t_point end, unsigned long color);
void						ft_set_spawn(t_data *data);
void						ft_fps(t_data *data);
t_point						ft_create_point(float x, float y);
void						swap(t_sprite *xp, t_sprite *yp);
void						sort_sprites(t_data *vars);
unsigned long				ft_dimmed_color(unsigned long color,
							float distance);
void						ft_draw_aaline(t_data *data, t_point point_a,
							t_point point_b, int r, int g, int b);
void						ft_shadow_shader(t_data *data);
int							ft_init_texture(t_data *data, t_texture *texture,
							char *path);
void						ft_draw_texture(t_data *data, t_wall wall,
							t_ray ray, int x);
int							convert_map(t_data *data);
void						ft_movement(t_data *data);
void						calculate_sprite_distance(t_data *data);
void						calculate_sprite_start(t_data *data);
void						ft_calculate_ray(t_data *data, t_ray *ray,
							t_wall *wall, int x);
void						ft_check_walls(t_data *data, t_ray *ray);
void						ft_select_texture(t_data *data, t_ray *ray,
							t_texture *texture);
void						ft_calculate_walls(t_data *data, t_wall *wall,
							t_ray *ray);
int							render(t_data *data);
void						ft_screenshot(t_data *data);
#endif
