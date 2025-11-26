/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:20:27 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 14:23:52 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

char	get_player_pos(t_player *plyr, char **map)
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
				plyr->posX = x + 0.5;
				plyr->posY = y + 0.5;
				return (map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	set_plane(t_player *plyr, char **map)
{
	char	c;

	c = get_player_pos(plyr, map);
	if (c == 'N')
	{
		plyr->plnX = 0.66;
		plyr->plnY = 0;
	}
	else if (c == 'E')
	{
		plyr->plnX = 0;
		plyr->plnY = 0.66;
	}
	else if (c == 'S')
	{
		plyr->plnX = -0.66;
		plyr->plnY = 0;
	}
	else if (c == 'W')
	{
		plyr->plnX = 0;
		plyr->plnY = -0.66;
	}
}

void	set_direction(t_player *plyr, char **map)
{
	char	c;

	c = get_player_pos(plyr, map);
	if (c == 'N')
	{
		plyr->dirX = 0;
		plyr->dirY = -1;
	}
	else if (c == 'E')
	{
		plyr->dirX = -1;
		plyr->dirY = 0;
	}
	else if (c == 'S')
	{
		plyr->dirX = 0;
		plyr->dirY = 1;
	}
	else if (c == 'W')
	{
		plyr->dirX = 1;
		plyr->dirY = 0;
	}
}

void	ft_init_player(t_game *game, char **map)
{
	game->plyr = malloc(sizeof(t_player));
	if (!game->plyr)
		return ;
	get_player_pos(game->plyr, map);
	set_direction(game->plyr, map);
	set_plane(game->plyr, map);
	game->plyr->moveSpeed = 0.05;
	game->plyr->rotSpeed = 0.03;
}
