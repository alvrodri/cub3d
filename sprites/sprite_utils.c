/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:35:04 by alvrodri          #+#    #+#             */
/*   Updated: 2020/10/26 10:15:45 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	swap(t_sprite *xp, t_sprite *yp)
{
	t_sprite	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	sort_sprites(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->sprites_n - 1)
	{
		j = 0;
		while (j < vars->sprites_n - i - 1)
		{
			if (vars->sprites[j].distance <= vars->sprites[j + 1].distance)
				swap(&vars->sprites[j], &vars->sprites[j + 1]);
			j++;
		}
		i++;
	}
}
