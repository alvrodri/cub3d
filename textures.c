/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 10:18:28 by alvrodri          #+#    #+#             */
/*   Updated: 2020/09/01 10:26:38 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_texture(t_data *data, t_texture *texture, char *path)
{
	(*texture).img.img = mlx_xpm_file_to_image(data->mlx_ptr, path,
		&(*texture).width, &(*texture).height);
	(*texture).img.addr = (unsigned int*)mlx_get_data_addr((*texture).img.img,
		&(*texture).img.bits_per_pixel, &(*texture).img.line_length,
			&(*texture).img.endian);
}
