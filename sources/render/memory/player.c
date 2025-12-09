/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:20:27 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/09 11:05:19 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

char	get_player_pos(t_actor *plyr, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (is_player(map[y][x]))
			{
				plyr->pos_x = x + 0.5;
				plyr->pos_y = y + 0.5;
				return (map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	set_plane(t_actor *plyr, char **map)
{
	char	c;

	c = get_player_pos(plyr, map);
	if (c == 'N')
	{
		plyr->plane_x = 0.66;
		plyr->plane_y = 0;
	}
	else if (c == 'E')
	{
		plyr->plane_x = 0;
		plyr->plane_y = -0.66;
	}
	else if (c == 'S')
	{
		plyr->plane_x = -0.66;
		plyr->plane_y = 0;
	}
	else if (c == 'W')
	{
		plyr->plane_x = 0;
		plyr->plane_y = 0.66;
	}
}

void	set_direction(t_actor *plyr, char **map)
{
	char	c;

	c = get_player_pos(plyr, map);
	if (c == 'N')
	{
		plyr->dir_x = 0;
		plyr->dir_y = -1;
	}
	else if (c == 'E')
	{
		plyr->dir_x = -1;
		plyr->dir_y = 0;
	}
	else if (c == 'S')
	{
		plyr->dir_x = 0;
		plyr->dir_y = 1;
	}
	else if (c == 'W')
	{
		plyr->dir_x = 1;
		plyr->dir_y = 0;
	}
}

void	ft_init_player(t_game *game, char **map)
{
	game->plyr = malloc(sizeof(t_actor));
	if (!game->plyr)
		return ;
	get_player_pos(game->plyr, map);
	set_direction(game->plyr, map);
	set_plane(game->plyr, map);
	game->plyr->move_speed = 0.05;
	game->plyr->rot_speed = 0.03;
}
