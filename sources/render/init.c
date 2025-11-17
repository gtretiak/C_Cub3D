/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:43:06 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/17 16:49:38 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

//* typedef struct s_player
//* {
//* 	double posX;
//* 	double posY;
//* 	double dirX;
//* 	double dirY;
//* 	double camX;
//* 	double camY;
//* }	t_player;

int is_player(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'E')
		return (90);
	if (c == 'S')
		return (180);
	if (c == 'W')
		return (270);

	return (-1);
}

t_player *init_player_pos(char **map)
{
	t_player *player;
	int y;
	int x;

	y = 0;

	while(map[y] != NULL)
	{
		x = 0;
		while(map[y][x] != '\0')
		{
			if(is_player(map[y][x]) != -1)
				break;
			x++;
		}
		y++;
	}

	player->posX = x;
	player->posY = y;
	return player;
}
void init_map_size(int height, int width, char **map)
{
	int i;
	int max;

	max = 0;
	while(map[i] != NULL)
	{
		if(ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	height = i;
	width = max;
}

//* typedef struct s_game
//* {
//* 	char	**map;
//* 	int		res_height;
//* 	int		res_width;
//* 	int		map_width;
//* 	int		map_height;
//* 	double time;
//* 	double prev_time;
//* 	t_player *player;
//* }	t_game;

void ft_init_game(t_game *game,char **map, char **textures)
{
	//TODO game->xpms = init_xpms(textures);

	game->map = map;
	game->player = init_player_pos(map);
	game->res_width = 480;
	game->res_height = 640;
	game->player->dirX = -1;
	game->player->dirY = 0;
	game->player->camX = 0;
	game->player->camY = 0.66;
	game->time = 0;
	game->prev_time = 0;
	game->prev_time = 0;
	init_map_size(&game->map_height,&game->map_width, map);
}
