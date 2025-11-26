#ifndef RENDER_H
# define RENDER_H


# include "../../cub3d.h"
# include "sys/time.h"
# include "math.h"

# define RESH 360
# define RESW 640

typedef struct s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double plnX;
	double plnY;
	double moveSpeed;
	double rotSpeed;

}	t_player;

typedef struct s_image
{
	void *img_ptr;
	char *pxl_ptr;
	int bpp;
	int endian;
	int line_len;
}	t_image;

typedef struct s_render_vars
{

}	t_render_vars;

typedef struct s_game
{
	char			**map;
	double			time;
	double			prev_time;
	t_image 		*mlx;
	t_image 		*txtr[4];
	t_player		*plyr;
	unsigned int	*colors;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*xpms[4];

}	t_game;

double	ft_get_current_time(void);
int		ft_keypress(int key, t_game *game);
int		ft_quit_game(void);
void	ft_init_player(t_game *game, char **map);
void	ft_init_struct(t_game *game,char **map, char **textures, unsigned int **colors);
void	ft_custom_pixel_put(t_image *img, int x, int y, unsigned int color);
void	ft_calc_speed(t_game *game);
void	ft_draw_column(int x, int drawStart, int drawEnd, t_game *game, unsigned int wall);

#endif
