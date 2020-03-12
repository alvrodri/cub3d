/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:16:34 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/10 15:40:51 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define W 119
//macos: 13
#define A 97
//macos: 0
#define S 115
//macos: 1
#define D 100
//macos: 2
#define ESC 65307
//macos: 53
#define SHIFT 65505
#define SPACE 32

int		ft_handle_key_press(int keycode, t_data *data)
{
	if (keycode == W)
		data->player->keys->w = 1;
	else if (keycode == A)
		data->player->keys->a = 1;
	else if (keycode == S)
		data->player->keys->s = 1;
	else if (keycode == D)
		data->player->keys->d = 1;
	else if (keycode == SHIFT)
		data->player->keys->shift = 1;
	else if (keycode == SPACE)
		data->player->keys->space = 1;
	return (1);
}

int		ft_handle_key_release(int keycode, t_data *data)
{
	if (keycode == ESC)
		return (ft_close(data));
	else if (keycode == W)
		data->player->keys->w = 0;
	else if (keycode == A)
		data->player->keys->a = 0;
	else if (keycode == S)
		data->player->keys->s = 0;
	else if (keycode == D)
		data->player->keys->d = 0;
	else if (keycode == SHIFT)
		data->player->keys->shift = 0;
	else if (keycode == SPACE)
		data->player->keys->space = 0;
	return (1);
}
