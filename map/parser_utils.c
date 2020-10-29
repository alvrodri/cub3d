/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 10:13:06 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/29 11:34:00 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		empty_end_of_line(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	flood_fill(t_data *data, int x, int y, int prev_color)
{
	if (x < 0 || x >= data->map.width || y < 0 || y >= data->map.height)
		return ;
	if (data->map.map[y][x] != prev_color)
		return ;
	data->map.map[y][x] = '9';
	flood_fill(data, x + 1, y, prev_color);
	flood_fill(data, x - 1, y, prev_color);
	flood_fill(data, x, y + 1, prev_color);
	flood_fill(data, x, y - 1, prev_color);
}

void	set_player_dir(t_data *data, int type)
{
	if (type == 'S')
	{
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	else if (type == 'E')
	{
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (type == 'W')
	{
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
}

int		check_player_pos(t_data *data, int y, char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		if (ft_strchr("NESW", str[x]))
		{
			if (data->player.x != -1 || data->player.y != -1)
				return (0);
			set_player_dir(data, str[x]);
			data->player.x = y + 0.5;
			data->player.y = x + 0.5;
			data->map.map[y][x] = '0';
		}
		x++;
	}
	return (1);
}

int		convert_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			if (data->map.map[i][j] == '9')
				data->map.map[i][j] = '0';
			else if (data->map.map[i][j] == '8')
				data->map.map[i][j] = '2';
			j++;
		}
		i++;
	}
	return (1);
}
