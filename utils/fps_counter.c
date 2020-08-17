/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:50:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/31 10:02:54 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <time.h>

void		ft_fps(t_data *data)
{
	static unsigned long	last_time;
	static int				count;

	if (data->fps == -1)
		data->fps = 60;
	if (time(0) - last_time > 1)
	{
		data->fps = count;
		last_time = time(0);
		count = 0;
	}
	else
		count++;
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 15, 0x123456,ft_strjoin("FPS: ", ft_itoa(data->fps)));
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 25, 0x123456, ft_strjoin("DIR: ", ft_itoa(data->player->dir)));
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 35, 0x123456, ft_strjoin("X, Y: ", ft_strjoin(ft_strjoin(ft_itoa(data->player->x), ", "), ft_itoa(data->player->y))));
}