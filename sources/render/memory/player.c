/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:20:27 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 11:57:15 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void	get_player_pos(t_player *plyr, char **map)
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
				return ;
			}
			x++;
		}
		y++;
	}
}

void	ft_init_player(t_game *game, char **map)
{
	game->plyr = malloc(sizeof(t_player));
	if (!game->plyr)
		return ;
	get_player_pos(game->plyr, map);
	game->plyr->dirX = -1;
	game->plyr->dirY = 0;
	game->plyr->plnY = 0.66;
	game->plyr->plnX = 0;
	game->plyr->moveSpeed = 0.05;
	game->plyr->rotSpeed = 0.03;
}
