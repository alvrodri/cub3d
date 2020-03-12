/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:39:07 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/09 16:39:10 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_close(t_data *data)
{
	if (data->player)
	{
		data->player->keys ? free(data->player->keys) : 0;
		free(data->player);
	}
	exit(1);
	return (1);
}

unsigned	int	ft_get_color(int x, int y, int map[24][24])
{
	if (map[x][y] == 1)
		return (0x999999);
	else if (map[x][y] == 2)
		return (0x624A2E);
	else
		return (0xFFFFFF);
}

void	ft_send_instructions(t_data *data)
{
	t_keys *keys;
	
	keys = data->player->keys;
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 15, 0xFFFF00, "Forward: ");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 60, 15, keys->w ? 0xFF0000 : 0xFFFF00, "W");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 25, 0xFFFF00, "Left: ");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 45, 25, keys->a ? 0xFF0000 : 0xFFFF00, "A");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 35, 0xFFFF00, "Backwards: ");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 70, 35, keys->s ? 0xFF0000 : 0xFFFF00, "S");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 45, 0xFFFF00, "Right: ");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 50, 45, keys->d ? 0xFF0000 : 0xFFFF00, "D");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 10, 55, 0xFFFF00, "Run: ");
	mlx_string_put(data->mlx_ptr, data->mlx_win, 40, 55, keys->shift ? 0xFF0000 : 0xFFFF00, "SHIFT");
}

void	ft_draw_pixel(t_data *data, int x, int y, unsigned int color)
{
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	((int *)mlx_get_data_addr(data->mlx_img, &bits_per_pixel, &size_line, &endian))[y * WIDTH + x] = color;
}