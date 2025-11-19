#ifndef RENDER_H
# define RENDER_H

#include "../../cub3d.h"
#include "sys/time.h"
#include "math.h"

typedef struct s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double plnX;
	double plnY;
}	t_player;

typedef struct s_game
{
	char		**map;
	double		time;
	double		prev_time;
	int			map_width;
	int			map_height;
	int			res_width;
	int			res_height;
	t_player	*player;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*xpms[4];
}	t_game;

void	ft_init_game(t_game *game,char **map, char **textures);
int		ft_keypress(int key);
int		ft_quit_game(void);

#endif
