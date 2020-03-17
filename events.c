/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:16:34 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/12 19:51:13 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define W 13
//macos: 13
#define A 0
//macos: 0
#define S 1
//macos: 1
#define D 2
//macos: 2
#define ESC 53
//macos: 53
#define SHIFT 65505
#define UP 65362
#define DOWN 65364
#define LEFT 65361
#define RIGHT 65363

int		ft_handle_key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->keys->w = 1;
	else if (keycode == A || keycode == LEFT)
		data->player->keys->a = 1;
	else if (keycode == S)
		data->player->keys->s = 1;
	else if (keycode == D || keycode == RIGHT)
		data->player->keys->d = 1;
	else if (keycode == SHIFT)
		data->player->keys->shift = 1;
	else if (keycode == UP)
		data->player->keys->up = 1;
	else if (keycode == DOWN)
		data->player->keys->down = 1;
	return (1);
}

int		ft_handle_key_release(int keycode, t_data *data)
{
	if (keycode == ESC)
		return (ft_close(data, 0));
	else if (keycode == W)
		data->player->keys->w = 0;
	else if (keycode == A || keycode == LEFT)
		data->player->keys->a = 0;
	else if (keycode == S)
		data->player->keys->s = 0;
	else if (keycode == D || keycode == RIGHT)
		data->player->keys->d = 0;
	else if (keycode == SHIFT)
		data->player->keys->shift = 0;
	else if (keycode == UP)
		data->player->keys->up = 0;
	else if (keycode == DOWN)
		data->player->keys->down = 0;
	return (1);
}
