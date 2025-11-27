/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:40:28 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/27 11:45:56 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void	get_texture_side(t_ray_vars *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			ray->tex_num = 1;
		else
			ray->tex_num = 3;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			ray->tex_num = 2;
		else
			ray->tex_num = 0;
	}
}

void	ft_calc_texture(t_game *game, t_ray_vars *ray)
{
	get_texture_side(ray);
	if (ray->side == 0)
		ray->wall_x = game->plyr->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->plyr->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	ray->tex_step = 1.0 * 64 / ray->wall_height;
	ray->tex_pos = (ray->draw_start - RESH / 2 + ray->wall_height)
		* ray->tex_step;
}
