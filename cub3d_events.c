/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 16:16:34 by alvrodri          #+#    #+#             */
/*   Updated: 2020/03/09 16:19:05 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_handle_key_release(int keycode, t_data *data)
{
	if (keycode == 53)
		return (ft_close(data));
	return (1);
}
