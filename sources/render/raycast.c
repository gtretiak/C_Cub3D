/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:52:17 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/16 10:14:47 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	prep_dda(t_game *game, t_ray_vars *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->plyr->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->plyr->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->plyr->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->plyr->pos_y)
			* ray->delta_dist_y;
	}
}

void	init_vars(t_game *game, t_ray_vars *ray)
{
	ray->cam_x = 2 * ray->x / (double) RESW - 1;
	ray->ray_dir_x = game->plyr->dir_x + game->plyr->plane_x * ray->cam_x;
	ray->ray_dir_y = game->plyr->dir_y + game->plyr->plane_y * ray->cam_x;
	ray->map_x = (int)game->plyr->pos_x;
	ray->map_y = (int)game->plyr->pos_y;
	ray->hit = 0;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	prep_dda(game, ray);
}

void	calc_distance(t_ray_vars *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->wall_height = (int)(RESH / ray->perp_wall_dist);
	ray->draw_start = -ray->wall_height / 2 + RESH / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_height / 2 + RESH / 2;
	if (ray->draw_end >= RESH)
		ray->draw_end = RESH - 1;
}

void	find_wall(t_game *game, t_ray_vars *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	calc_distance(ray);
}

int	ft_raycast(t_game *game)
{
	t_ray_vars	ray;

	ray.x = 0;
	while (ray.x < RESW)
	{
		init_vars(game, &ray);
		find_wall(game, &ray);
		ft_calc_texture(game, &ray);
		ft_draw_image(game, &ray);
		ft_calc_speed(game);
		(ray.x)++;
	}
	ft_handle_movement(game);
	ft_rotate(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->mlx->img_ptr, 0, 0);
	return (0);
}
