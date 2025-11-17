#ifndef RENDER_H
# define RENDER_H

#include "../../cub3d.h"

typedef struct s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double camX;
	double camY;
}	t_player;

typedef struct s_game
{
	int			res_width;
	int			res_height;
	int			map_width;
	int			map_height;
	void		*xpms[4];
	char		**map;
	double		time;
	double		prev_time;
	t_player	*player;
}	t_game;

void ft_init_game(t_game *game,char **map, char **textures);

#endif
