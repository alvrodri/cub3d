/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:23:56 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/26 10:39:36 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_variables(t_data *vars)
{
	if (vars->height == -1 || vars->width == -1
		|| vars->textures.north.height == -1 || vars->textures.south.height
			== -1
		|| vars->textures.east.height == -1 || vars->textures.west.height == -1
		|| vars->textures.sprite.height == -1 || vars->textures.floor[0] == -1
		|| vars->textures.floor[1] == -1 || vars->textures.floor[2] == -1
		|| vars->textures.ceiling[0] == -1 || vars->textures.ceiling[1] == -1
		|| vars->textures.ceiling[2] == -1)
		return (0);
	return (1);
}

void	initialize_vars(t_data *vars)
{
	vars->width = -1;
	vars->height = -1;
	vars->textures.north.height = -1;
	vars->textures.south.height = -1;
	vars->textures.east.height = -1;
	vars->textures.west.height = -1;
	vars->textures.sprite.height = -1;
	vars->textures.floor[0] = -1;
	vars->textures.floor[1] = -1;
	vars->textures.floor[2] = -1;
	vars->textures.ceiling[0] = -1;
	vars->textures.ceiling[1] = -1;
	vars->textures.ceiling[2] = -1;
	vars->map.height = 0;
	vars->map.width = 0;
	vars->player.x = -1;
	vars->player.y = -1;
	vars->sprites_n = 0;
}
