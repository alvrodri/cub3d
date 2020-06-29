#include "cub3d.h"

void    ft_accelerate(t_data *data)
{
	t_player *player = data->player;

	if (player->keys->s == 1)
	{
		if (player->current_speed > MIN_SPEED)
			player->current_speed -= 0.0005;
	}
	else
	{
		if (player->keys->w == 1)	
		{
			if (player->current_speed < MAX_SPEED)
				player->current_speed += 0.0005;
		}
		else if (player->keys->w == 0)
		{
			if (player->current_speed > 0)
				player->current_speed -= 0.005;
			if (player->current_speed < 0)
				player->current_speed = 0;
		}
	}
}