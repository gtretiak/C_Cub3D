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

typedef struct s_image
{
	void *img_ptr;
	char *img_pixels_ptr;
	int bits_per_pixel;
	int line_len;
	int endian;
}	t_image;

typedef struct s_game
{
	char			**map;
	double			time;
	double			prev_time;
	int				map_width;
	int				map_height;
	int				res_width;
	int				res_height;
	t_image 		*img;
	t_player		*player;
	unsigned int	*colors;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*xpms[4];

}	t_game;

void	ft_init_game(t_game *game,char **map, char **textures, unsigned int **colors);
void	ft_custom_pixel_put(t_image *img, int x, int y, unsigned int color);
void ft_draw_column(int x, int drawStart, int drawEnd, t_game *game, unsigned int wall);
int		ft_keypress(int key);
double	ft_get_current_time(void);
int		ft_quit_game(void);

#endif
