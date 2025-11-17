#ifndef RENDER_H
# define RENDER_H

#include "../../cub3d.h"

typedef struct s_player
{
	int posX;
	int posY;
	int dirX;
	int dirY;
}	t_player;

typedef struct s_game
{
	char	**map;
	int		res_height;
	int		res_width;
	int		map_width;
	int		map_height;
	t_player *player;
}	t_game;

t_game	*ft_init_game(char **map);

#endif
