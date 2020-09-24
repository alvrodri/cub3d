/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 10:22:31 by alvrodri          #+#    #+#             */
/*   Updated: 2020/09/03 11:50:32 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_draw_texture(t_data *data, t_wall wall, t_texture texture, int x)
{
	float y_increment = (wall.height * 2) / texture.height;
    float y = data->height / 2 - wall.height;

	for (int i = 0; i < texture.height; i++)
	{
		ft_draw_line(data, ft_create_point(x, y), ft_create_point(x, y + y_increment),
			texture.img.addr[i * texture.width + wall.texture_x]);
		y += y_increment;
	}
}