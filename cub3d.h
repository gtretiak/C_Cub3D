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
# include "lib/minilibx-linux/mlx.h"
# include "lib/libft/libft.h"

# ifndef HEIGHT
#  define HEIGHT 800
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# define MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
# define MAP_PLAYER "Error.\nThere can't be more than one player.\n"
# define MAP_UNEXPECTED "Error.\nUnexpected char found in the map.\n"
# define MAP_GAPS "Error.\nThere can't be gaps (empty lines) in the map.\n"
# define MAP_LAST "Error.\nThe map must be the last element of *.cub.\n"
# define MAP_NO "Error.\nThere is no map in your cub file.\n"
# define ELEMENT_TYPE "Error.\nElement type is missing (invalid).\n"
# define ELEMENT_UNEXPECTED "Error.\nUnexpected char found in an element.\n"
# define ELEMENT_PATH "Error.\nTexture path/file is invalid/inaccessible.\n"

typedef struct s_img
{
	void	*img;
	char	*pixels;
	int	bpp;
	int	line_len;
	int	endian;
}	t_img;

// structure for a player TODO

typedef struct	s_flat
{
	char	type;
	char	*rgb;
}	t_flat;

typedef struct	s_wall
{
	char	*type;
	char	*path;
}	t_wall;

typedef struct	s_map
{
	t_flat	floor;
	t_flat	ceilling;
	t_wall	north;
	t_wall	south;
	t_wall	west;
	t_wall	east;
	char	**map;
	bool	flag;
}	t_map;

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

bool args_checker(char *map_path);
void	file_reading(char *file, t_map *map);
int	parse_map(char *line, t_map *map);

void	init(t_mlx *game);

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
