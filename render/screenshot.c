/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 11:04:55 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/29 11:44:01 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_int_to_bytes(unsigned char *header, int n)
{
	header[0] = (unsigned char)n;
	header[1] = (unsigned char)(n >> 8);
	header[2] = (unsigned char)(n >> 16);
	header[3] = (unsigned char)(n >> 24);
}

void	ft_print_colors(t_data *data, int fd)
{
	int	i;

	i = data->width * data->height - 1;
	while (i > 0)
	{
		write(fd, &data->img.addr[i], 3);
		i--;
	}
}

void	ft_screenshot(t_data *data)
{
	unsigned char	header[54];
	int				fd;

	if (data->screenshot)
	{
		fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777 |
			O_TRUNC | O_APPEND);
		if (fd == -1)
			ft_close(data, 1);
		render(data);
		ft_bzero(header, 54);
		header[0] = (unsigned char)'B';
		header[1] = (unsigned char)'M';
		ft_int_to_bytes(header + 2, 54 + (3 * data->width *
			data->height) + ((4 - (data->width * 3) % 4) % 4 * data->height));
		header[10] = (unsigned char)54;
		header[14] = (unsigned char)40;
		ft_int_to_bytes(header + 18, data->width);
		ft_int_to_bytes(header + 22, data->height);
		header[26] = (unsigned char)1;
		header[28] = (unsigned char)24;
		write(fd, header, 54);
		ft_print_colors(data, fd);
		close(fd);
	}
}
