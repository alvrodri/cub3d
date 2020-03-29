/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:29:04 by alvaro            #+#    #+#             */
/*   Updated: 2020/03/12 22:43:01 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_map(t_data *data, char *map)
{
	int		fd;
	int		read;
	char	*line;
	char	**split;

	fd = open(map, O_RDONLY);
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
	}
}