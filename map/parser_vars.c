/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 11:23:56 by alvrodri          #+#    #+#             */
/*   Updated: 2020/11/02 10:39:05 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		check_extension(char *path, char *extension)
{
	size_t	len;
	size_t	extension_len;
	char	*tmp;

	len = ft_strlen(path);
	extension_len = ft_strlen(extension);
	if (len < extension_len)
		return (0);
	tmp = ft_substr(path, len - extension_len, len);
	if (ft_strncmp(tmp, extension, extension_len) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

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
