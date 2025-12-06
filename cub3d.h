/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:09:41 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 16:50:57 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define ARG_NUM "No/Many arguments. Should be \'./cub3D <map.cub>\'\n"
# define ARG_INV "Invalid file. Should be \'.cub\'.\n"
# define MAP_INV "Error.\nInvalid map: not closed/weird char/contains gaps.\n"
# define MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
# define MAP_PLAYER "Error.\nThere can't be more than one player.\n"
# define MAP_NO_PLAYER "Error.\nThere is no player.\n"
# define MAP_NO_FLOOR "Error.\nThere is no floor.\n"
# define MAP_NO_CEILLING "Error.\nThere is no ceilling.\n"
# define MAP_NO_WALL "Error.\nOne or more walls are missing.\n"
# define MAP_UNEXPECTED "Error.\nUnexpected char found in the map.\n"
# define MAP_GAPS "Error.\nThere can't be gaps (empty lines) in the map.\n"
# define MAP_LAST "Error.\nThe map must be the last element of *.cub.\n"
# define MAP_NO "Error.\nThere is no map in your cub file.\n"
# define ELEMENT_TYPE "Error.\nElement type is missing or doubled (invalid).\n"
# define ELEMENT_UNEXPECTED "Error.\nUnexpected char found in an element.\n"
# define ELEMENT_PATH "Error.\nTexture path/file is invalid/inaccessible.\n"

typedef struct s_img
{
	void	*img;
	char	*pixels;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	bool	on_position;
	char	direction;
	t_point	point;
}	t_player;

typedef struct s_flat
{
	bool	installed;
	int		rgb[3];
	int		color;
}	t_flat;

typedef struct s_wall
{
	bool	installed;
	char	*path;
}	t_wall;

typedef struct s_scene
{
	t_flat		floor;
	t_flat		ceilling;
	t_wall		north;
	t_wall		south;
	t_wall		west;
	t_wall		east;
	t_player	player;
	t_point		map_size;
	char		**map;
	int			map_row;
	int			flag;
}	t_scene;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

void	args_checker(int argc, char **argv);

int		file_reading(char *file, t_scene *scene);
void	init_scene(char *file, t_scene *scene);

int		define_wall(char *line, t_scene *scene);
int		set_flat(char *line, t_scene *scene);
int		build_map(char *line, t_scene *scene);
void	parse_map(int fd, t_scene *scene);

void	init_game(t_mlx *game);

void	event_listening(t_mlx *game);
int		handle_key(int keysym, t_mlx *game);
int		key_movement(int keysym, t_mlx *game);
int		key_control(int keysym, t_mlx *game);
int		handle_mini(t_mlx *game);
int		handle_action(t_mlx *game);
int		handle_mouse(int button, int x, int y, t_mlx *game);
int		handle_closing(t_mlx *game);

void	rendering(t_mlx *game);
void	put_pixels(int x, int y, t_img *img, int color);

void	free_scene(t_scene *scene);
void	malloc_error(void);
void	exiter(char *str);
int		returner(char *str);

#endif
