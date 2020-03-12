/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvaro <alvaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 19:29:04 by alvaro            #+#    #+#             */
/*   Updated: 2020/03/12 20:03:50 by alvaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_map(t_data *data, char *map)
{
	int		fd;
	int		read;
	char	*line;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		ft_close(data, 1);
	while ((read = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == 'R')
		{
			data->width = ft_atoi(ft_split(line, ' ')[1]);
			data->height = ft_atoi(ft_split(line, ' ')[2]);
		}
		else if (line[0] == 'F')
		{
			
		}
		else if (line[0] == 'C')
		{
			
		}
	}
}