/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 10:09:30 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/29 12:51:51 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		detect_textures_type(t_data *vars, char *str)
{
	int	i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		return (parse_texture_line(vars, 1, &str[i]));
	else if (str[i] == 'S' && str[i + 1] == 'O')
		return (parse_texture_line(vars, 2, &str[i]));
	else if (str[i] == 'E' && str[i + 1] == 'A')
		return (parse_texture_line(vars, 3, &str[i]));
	else if (str[i] == 'W' && str[i + 1] == 'E')
		return (parse_texture_line(vars, 4, &str[i]));
	else if (str[i] == 'S')
		return (parse_texture_line(vars, 5, &str[i]));
	return (0);
}

int		detect_line_type(t_data *vars, char *str)
{
	int i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	if (str[i] == 'R')
		return (parse_resolution_line(vars, &str[i]));
	if (ft_strchr("NSEW", str[i]))
		return (detect_textures_type(vars, &str[i]));
	else if (str[i] == 'C')
		return (parse_color_line(vars, 1, &str[i]));
	else if (str[i] == 'F')
		return (parse_color_line(vars, 2, &str[i]));
	else if (ft_strchr("012", str[i]) || ft_isspace(str[i]))
		return (count_map_size(vars, str));
	return (0);
}

int		check_file(t_data *vars, int fd)
{
	char	*line;
	int		ret;
	int		correct_line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		correct_line = detect_line_type(vars, line);
		free(line);
		if (correct_line == 0)
			return (0);
	}
	correct_line = detect_line_type(vars, line);
	free(line);
	if (correct_line == 0)
		return (0);
	if (vars->map.height < 4 || vars->map.width < 4)
		return (0);
	return (1);
}

int		check_map(t_data *vars)
{
	int i;

	i = 0;
	while (i < vars->map.width)
	{
		if (vars->map.map[0][i] == '9'
			|| vars->map.map[vars->map.height - 1][i] == '9')
			return (0);
		i++;
	}
	i = 0;
	while (i < vars->map.height)
	{
		if (vars->map.map[i][0] == '9'
			|| vars->map.map[i][vars->map.width - 1] == '9')
			return (0);
		i++;
	}
	return (1);
}

int		read_file(t_data *vars, int args_n, char **args)
{
	int fd;
	int	map_ok;

	if (args_n < 2 || args_n > 3 || (args_n == 3 && ft_strncmp(args[2],
		"--save", 6) != 0))
		return (0);
	initialize_vars(vars);
	if ((fd = open(args[1], O_RDONLY)) == -1)
		return (0);
	if (!check_file(vars, fd))
		return (0);
	if (close(fd) == -1)
		return (0);
	if ((fd = open(args[1], O_RDONLY)) == -1)
		return (0);
	if (!parse_map(vars, fd))
		return (0);
	flood_fill(vars, vars->player.x, vars->player.y, '0');
	map_ok = check_map(vars);
	convert_map(vars);
	vars->sprites = malloc(sizeof(t_sprite) * vars->sprites_n);
	vars->zbuffer = malloc(sizeof(float) * vars->width);
	check_sprites_amount(vars);
	close(fd);
	return (map_ok == 1) ? 1 : 0;
}
