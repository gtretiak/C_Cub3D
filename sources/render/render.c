/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:52:17 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/27 11:11:54 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void prep_dda(t_game *game, t_ray_vars *ray)
{
	if(ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->plyr->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->plyr->pos_x) * ray->delta_dist_x;
	}
	if(ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->plyr->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->plyr->pos_y) * ray->delta_dist_y;
	}
}

void init_vars(t_game *game, t_ray_vars *ray)
{
	ray->cam_x = 2 * ray->x / (double) RESW - 1;
	ray->ray_dir_x = game->plyr->dir_x + game->plyr->plane_x * ray->cam_x;
	ray->ray_dir_y = game->plyr->dir_y + game->plyr->plane_y * ray->cam_x;
	ray->map_x = (int)game->plyr->pos_x;
	ray->map_y = (int)game->plyr->pos_y;
	ray->hit = 0;
	if(ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1/ray->ray_dir_x);
	if(ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1/ray->ray_dir_y);
	prep_dda(game, ray);
}

void calc_distance(t_ray_vars *ray)
{
	if(ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->wall_height = (int) (RESH / ray->perp_wall_dist);
	ray->draw_start = -ray->wall_height / 2 + RESH / 2;
	if(ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_height / 2 + RESH / 2;
	if(ray->draw_end >= RESH)
		ray->draw_end = RESH - 1;
}

void find_wall(t_game *game, t_ray_vars *ray)
{
	while(ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side=0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if(game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	calc_distance(ray);
}

void calc_texture(t_game *game, t_ray_vars *ray)
{
	ray->tex_num = game->map[ray->map_y][ray->map_x] - '1';
	if(ray->side == 0)
		ray->wall_x = game->plyr->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->plyr->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if(ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if(ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	ray->tex_step = 1.0 * 64 / ray->wall_height;
	ray->tex_pos = (ray->draw_start - RESH / 2 + ray->wall_height) * ray->tex_step;
}

void draw_image(t_game *game, t_ray_vars *ray)
{
	int y;
	int offset;
	unsigned int txtr_pixel;
	y = 0;
	while(y <= RESH)
	{
		if (y > ray->draw_end)
			ft_custom_pixel_put(game->mlx, ray->x, y, game->colors[0]);
		else if (y < ray->draw_start)
			ft_custom_pixel_put(game->mlx, ray->x, y, game->colors[1]);
		y++;
	}
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int) ray->tex_pos & (64 - 1);
		ray->tex_pos += ray->tex_step;
		offset = (game->txtr[ray->tex_num]->line_len * ray->tex_y) + (ray-> tex_x * (game->txtr[ray->tex_num]->bpp) / 8);
		txtr_pixel = *(unsigned int *)(game->txtr[ray->tex_num]->pxl_ptr + offset);
		ft_custom_pixel_put(game->mlx, ray->x, y, txtr_pixel);
		y++;
	}
}

int ft_raycast(t_game *game)
{
	t_ray_vars	ray;

	ray.x = 0;
	while(ray.x < RESW)
	{
		init_vars(game, &ray);
		find_wall(game, &ray);
		calc_texture(game, &ray);
		draw_image(game, &ray);
		ft_calc_speed(game);
		(ray.x)++;
	}
	ft_handle_movement(game);
	ft_rotate(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->mlx->img_ptr, 0, 0);

	return (0);
}

void ft_render(char **map, char **textures, unsigned int **colors)
{
	t_game game;

	ft_bzero(&game, sizeof(t_game));
	ft_init_struct(&game, map, textures, colors);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &ft_keypress, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &ft_keyrelease, &game);
	mlx_hook(game.win_ptr, DestroyNotify,
		StructureNotifyMask, &ft_quit_game, &game);
	mlx_loop_hook(game.mlx_ptr, ft_raycast, &game);
	mlx_loop(game.mlx_ptr);
}

int main(void)
{
	//! testing vars
	unsigned int color_bot[] = {75, 75, 75};
    unsigned int color_top[] = {50, 50, 255};
    unsigned int *colors[] = {color_bot, color_top};
	char *textures[] = {"./a.xpm","./wall.xpm","./a.xpm","./wall.xpm"};
	char *map[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"1111111110110000011100001",
		"1000000000110000011101111",
		"1111011111111101110000001",
		"1111011111111101110101001",
		"1100000011010101110000001",
		"1000000000000000110000001",
		"1000000000000000110101001",
		"11000001110101011110N0111",
		"11110111 1110101 10111101",
		"11111111 1111111 11111111",
		NULL
	};


	ft_render(map, textures, colors);
	return 0;
}
