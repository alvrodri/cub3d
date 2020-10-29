/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 10:19:38 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/29 12:56:17 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_null_texture(t_data *vars, int type)
{
	if (type == 1)
		return (vars->textures.north.height != -1 ? 0 : 1);
	else if (type == 2)
		return (vars->textures.south.height != -1 ? 0 : 1);
	else if (type == 3)
		return (vars->textures.east.height != -1 ? 0 : 1);
	else if (type == 4)
		return (vars->textures.west.height != -1 ? 0 : 1);
	else
		return (vars->textures.sprite.height != -1 ? 0 : 1);
	return (1);
}

int	save_texture_dir(t_data *vars, int type, char *str)
{
	if (!is_null_texture(vars, type))
		return (0);
	if (type == 1)
		vars->textures.north.path = ft_strdup(str);
	else if (type == 2)
		vars->textures.south.path = ft_strdup(str);
	else if (type == 3)
		vars->textures.east.path = ft_strdup(str);
	else if (type == 4)
		vars->textures.west.path = ft_strdup(str);
	else
		vars->textures.sprite.path = ft_strdup(str);
	return (1);
}

int	ft_init_texture(t_data *data, t_texture *texture, char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] != 'm')
		return (0);
	if ((fd = open(path, O_RDONLY)) == -1)
	{
		close(fd);
		return (0);
	}
	texture->img.img = mlx_xpm_file_to_image(data->mlx_ptr, texture->path,
							&texture->width, &texture->height);
	texture->img.addr = (unsigned int *)mlx_get_data_addr(texture->img.img,
		&texture->img.bits_per_pixel, &texture->img.line_length,
			&texture->img.endian);
	return (1);
}

int	ft_init_textures_type(t_data *data, int type)
{
	if (type == 1)
		return (ft_init_texture(data, &data->textures.north,
			data->textures.north.path));
	else if (type == 2)
		return (ft_init_texture(data, &data->textures.south,
			data->textures.south.path));
	else if (type == 3)
		return (ft_init_texture(data, &data->textures.east,
			data->textures.east.path));
	else if (type == 4)
		return (ft_init_texture(data, &data->textures.west,
			data->textures.west.path));
	else if (type == 5)
		return (ft_init_texture(data, &data->textures.sprite,
			data->textures.sprite.path));
		return (0);
}

int	parse_texture_line(t_data *vars, int type, char *str)
{
	int i;

	i = (type == 5) ? 1 : 2;
	if (!ft_isspace(str[i]))
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isascii(str[i]))
		return (0);
	if (!save_texture_dir(vars, type, &str[i]))
		return (0);
	if (!ft_init_textures_type(vars, type))
		return (0);
	return (1);
}
