/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:51:15 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/27 11:42:51 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void	draw_pixel(t_image *img, int x, int y, unsigned int color)
{
	int	offset;

	if (x >= 0 && x < 1280 && y >= 0 && y < 720)
	{
		offset = (img->line_len * y) + (x * (img->bpp / 8));
		*((unsigned int *)(offset + img->pxl_ptr)) = color;
	}
}

void	ft_draw_image(t_game *game, t_ray_vars *ray)
{
	int				y;
	int				offset;
	unsigned int	txtr_pixel;

	y = 0;
	while (y <= RESH)
	{
		if (y > ray->draw_end)
			draw_pixel(game->mlx, ray->x, y, game->colors[0]);
		else if (y < ray->draw_start)
			draw_pixel(game->mlx, ray->x, y, game->colors[1]);
		y++;
	}
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ray->tex_y = (int) ray->tex_pos & (64 - 1);
		ray->tex_pos += ray->tex_step;
		offset = (game->txtr[ray->tex_num]->line_len * ray->tex_y)
			+ (ray-> tex_x * (game->txtr[ray->tex_num]->bpp) / 8);
		txtr_pixel = *(unsigned int *)(game->txtr[ray->tex_num]->pxl_ptr
				+ offset);
		draw_pixel(game->mlx, ray->x, y, txtr_pixel);
		y++;
	}
}
