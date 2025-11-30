#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx_linux/mlx.h"
# include "C_libft/libft.h"

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# define ARG_NUM "No/Many arguments. Should be \'./cub3D <map.cub>\'\n" // DONE!
# define ARG_INV "Invalid file. Should be \'.cub\'.\n" // DONE!
# define MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
# define MAP_PLAYER "Error.\nThere can't be more than one player.\n" // DONE!
# define MAP_UNEXPECTED "Error.\nUnexpected char found in the map.\n" // DONE!
# define MAP_GAPS "Error.\nThere can't be gaps (empty lines) in the map.\n" // DONE!
# define MAP_LAST "Error.\nThe map must be the last element of *.cub.\n" // DONE!
# define MAP_NO "Error.\nThere is no map in your cub file.\n" // DONE!
# define ELEMENT_TYPE "Error.\nElement type is missing or doubled (invalid).\n" // DONE!
# define ELEMENT_UNEXPECTED "Error.\nUnexpected char found in an element.\n" // DONE!
# define ELEMENT_PATH "Error.\nTexture path/file is invalid/inaccessible.\n" // DONE!

typedef struct s_img
{
	void	*img;
	char	*pixels;
	int	bpp;
	int	line_len;
	int	endian;
}	t_img;

typedef struct	s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct	s_player
{
	bool	on_position;
	char	direction;
	t_point	point;
}	t_player;

typedef struct	s_flat
{
	int	rgb[3];
	int	color;
}	t_flat;

typedef struct	s_wall
{
	char	*path;
}	t_wall;

typedef struct	s_scene
{
	t_flat	floor;
	t_flat	ceilling;
	t_wall	north;
	t_wall	south;
	t_wall	west;
	t_wall	east;
	t_player	player;
	char	**map;
	int	flag;
}	t_scene;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

void	args_checker(int argc, char **argv);
int	file_reading(char *file, t_scene *scene);
void	init_scene(t_scene *scene);
void	free_scene(t_scene *scene);
int	parse_scene(char *line, t_scene *scene);

void	exiter(char *str);
void	init_game(t_mlx *game);

void	event_listening(t_mlx *game);
int	handle_key(int keysym, t_mlx *game);
int	key_movement(int keysym, t_mlx *game);
int	key_control(int keysym, t_mlx *game);
int	handle_mini(t_mlx *game);
int	handle_action(t_mlx *game);
int	handle_mouse(int button, int x, int y, t_mlx *game);
int	handle_closing(t_mlx *game);

void	rendering(t_mlx *game);
void	put_pixels(int x, int y, t_img *img, int color);

void	malloc_error(void);
#endif
