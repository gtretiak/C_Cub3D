/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:42:23 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/27 11:09:31 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "../../cub3d.h"
# include "sys/time.h"
# include "math.h"

# define RESH 360
# define RESW 640

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;

}	t_player;

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
	t_player		*plyr;
	int				move_x;
	int				move_y;
	int				rotate;
	unsigned int	*colors;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*xpms[4];

}	t_game;

double	ft_get_current_time(void);
int		ft_keypress(int key, t_game *game);
int		ft_keyrelease(int key, t_game *game);
int		ft_quit_game(void);
void	ft_init_player(t_game *game, char **map);
void	ft_init_struct(t_game *game, char **map,
			char **textures, unsigned int **colors);
void	ft_custom_pixel_put(t_image *img, int x, int y, unsigned int color);
void	ft_handle_movement(t_game *game);
void	ft_calc_speed(t_game *game);
void	ft_draw_column(int x, int drawStart, int drawEnd,
			t_game *game, unsigned int wall);
void	ft_rotate(t_game *game);

#endif
