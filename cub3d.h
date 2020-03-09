/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 18:25:06 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/09 16:39:26 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./minilibx/mlx.h"
# include "./libft/libft.h"
# include "unistd.h"
# include "stdio.h"
# include "stdlib.h"
# include "math.h"

typedef	struct	s_player {
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		time;
	double		old_time;
}				t_player;

typedef struct  s_data {
	void		*mlx_ptr;
	void		*mlx_win;
	t_player	*player;
}				t_data;

int		ft_close(t_data *data);
int		ft_handle_key_press(int keycode, t_data *data);
int		ft_handle_key_release(int keycode, t_data *data);

#endif
