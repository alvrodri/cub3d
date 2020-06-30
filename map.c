/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:29:04 by alvaro            #+#    #+#             */
/*   Updated: 2020/06/30 09:45:50 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int ft_strlen_char(char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			j++;
		i++;
	}
	return j;
}

static char *ft_strtrim_char(char *str, char c)
{
	char *new;
	int len;
	int i;
	int j;

	new = malloc(ft_strlen_char(str, c) + 1);
	len = ft_strlen_char(str, c);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return new;
}

static void	ft_second_read(t_data *data, int fd)
{
	char **map;
	char *line;
	int i;
	int j;

	i = 0;
	j = 0;
	map = malloc(data->map->y * sizeof(char *));
	while (get_next_line(fd, &line))
	{
		if (ft_strchr("012", line[0]))
		{
			map[i] = ft_strtrim_char(line, ' ');
			free(line);
			i++;
		}
	}

	data->map->map = map;
}

static void	ft_first_read(t_data *data, int fd, char **line, char *map_name)
{
	data->map->x = 0;
	data->map->y = 0;
	while (get_next_line(fd, line) > 0)
	{
		if (ft_strlen_char(*line, ' ') > data->map->x)
			data->map->x = ft_strlen_char(*line, ' ');
		data->map->y++;
	}
	if (ft_strlen_char(*line, ' ') > data->map->x)
			data->map->x = ft_strlen_char(*line, ' ');
	data->map->y++;
	ft_second_read(data, open(map_name, O_RDONLY));
}

void	ft_parse_map(t_data *data, char *map_name)
{
	int		fd;
	int		read;
	char	*line;
	char	**split;
	char	**map;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		ft_close(data, 1);
	data->map->size = 24;
	data->textures->ceiling = malloc(sizeof(t_texture));
	data->textures->floor = malloc(sizeof(t_texture));
	while ((read = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == 'R')
		{
			data->width = ft_atoi(ft_split(line, ' ')[1]);
			data->height = ft_atoi(ft_split(line, ' ')[2]);
		}
		else if (line[0] == 'F')
		{
			split = ft_split(ft_split(line, ' ')[1], ',');
			data->textures->floor->r = ft_atoi(split[0]);
			data->textures->floor->g = ft_atoi(split[1]);
			data->textures->floor->b = ft_atoi(split[2]);
			free(split);
		}
		else if (line[0] == 'C')
		{
			split = ft_split(ft_split(line, ' ')[1], ',');
			data->textures->ceiling->r = ft_atoi(split[0]);
			data->textures->ceiling->g = ft_atoi(split[1]);
			data->textures->ceiling->b = ft_atoi(split[2]);
			free(split);
		}
		else if (ft_strchr("012", line[0]))
		{
			free(line);
			ft_first_read(data, fd, &line, map_name);
			return;
		}
		free(line);
	}
}