/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 10:28:24 by alvrodri          #+#    #+#             */
/*   Updated: 2020/07/16 10:46:56 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static  int     ft_get_degrees(char cardinal)
{
    if (cardinal == 'E')
        return (0);
    else if (cardinal == 'N')
        return (90);
    else if (cardinal == 'W')
        return (180);
    else if (cardinal == 'S')
        return (270);
    return (0);
}

void            ft_set_spawn(t_data *data)
{
    int y;
    int x;

    y = 0;
    while (data->map->map[y])
    {
        x = 0;
        while (data->map->map[y][x])
        {
            if (ft_strchr("NSEW", data->map->map[y][x]))
            {
                if (data->player->x != -1 || data->player->y != -1)
                    ft_close(data, 1);
                data->player->dir = ft_get_degrees(data->map->map[y][x]);
                data->map->map[y][x] = '0';
                data->player->x = x;
                data->player->y = y;
            }
            x++;
        }
        y++;
    }
    if (data->player->x == -1 || data->player->y == -1)
        ft_close(data, 1);
}