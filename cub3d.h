/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:09:41 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/16 10:17:31 by rimagalh         ###   ########.fr       */
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
# include <sys/time.h>
# include "minilibx_linux/mlx.h"
# include "C_libft/libft.h"

# define RESH 360
# define RESW 640

# define ARG_NUM "No/Many arguments. Should be \'./cub3D <map.cub>\'\n"
# define ARG_INV "Invalid file. Should be \'.cub\'.\n"
# define MAP_INV "Error.\nInvalid map:small/open/contains weird char/gaps.\n"
# define MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
# define MAP_PLAYER "Error.\nThere can't be more than one player.\n"
# define MAP_NO_PLAYER "Error.\nThere is no player.\n"
# define MAP_NO_FLOOR "Error.\nThere is no floor.\n"
# define MAP_NO_CEILLING "Error.\nThere is no ceilling.\n"
# define MAP_NO_WALL "Error.\nOne or more walls are missing.\n"
# define MAP_UNEXPECTED "Error.\nUnexpected char found in the map.\n"
# define MAP_GAPS "Error.\nThere can't be gaps (empty lines) in the map.\n"
# define MAP_LAST "Error.\nThe map must be the last element of *.cub.\n"
# define MAP_NO "Error.\nThere's no map in cub file (or it's not closed).\n"
# define ELEMENT_TYPE "Error.\nElement type is missing or doubled (invalid).\n"
# define ELEMENT_UNEXPECTED "Error.\nUnexpected char found in an element.\n"
# define ELEMENT_PATH "Error.\nTexture path/file is invalid/inaccessible.\n"

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

typedef struct s_actor
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;

}	t_actor;

typedef struct s_image
{
	void	*img_ptr;
	char	*pxl_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}	t_image;

typedef struct s_ray_vars
{
	double	cam_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	wall_x;
	int		x;
	int		map_y;
	int		map_x;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	double	tex_step;
	double	tex_pos;
}	t_ray_vars;

typedef struct s_game
{
	char			**map;
	double			time;
	double			prev_time;
	t_image			*mlx;
	t_image			*txtr[4];
	t_actor			*plyr;
	int				move_x;
	int				move_y;
	int				rotate;
	unsigned int	*colors;
	void			*mlx_ptr;
	void			*win_ptr;
}	t_game;

void	args_checker(int argc, char **argv);
int		file_reading(char *file, t_scene *scene);
void	init_scene(char *file, t_scene *scene);
int		define_wall(char *line, t_scene *scene);
int		set_flat(char *line, t_scene *scene);
int		build_map(char *line, t_scene *scene);
void	parse_map(int fd, t_scene *scene);
void	free_scene(t_scene *scene);
void	malloc_error(t_scene *scene);
void	exiter(char *str);
int		returner(char *str);
double	ft_get_current_time(void);
int		ft_keypress(int key, t_game *game);
int		ft_keyrelease(int key, t_game *game);
int		ft_quit_game(t_game *game);
void	ft_init_player(t_game *game, char **map);
void	ft_init_struct(t_game *game, t_scene *scene);
void	ft_draw_image(t_game *game, t_ray_vars *ray);
void	ft_calc_texture(t_game *game, t_ray_vars *ray);
void	ft_handle_movement(t_game *game);
void	ft_calc_speed(t_game *game);
void	ft_rotate(t_game *game);
int		ft_raycast(t_game *game);
void	ft_free_game(t_game *game);
void	ft_render(t_scene *scene);

#endif
