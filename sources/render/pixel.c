/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:51:15 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/24 12:05:55 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void ft_custom_pixel_put(t_image *img, int x, int y, unsigned int color)
{
	int offset;

	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->img_pixels_ptr)) = color;
}
//! wall var is temp
void ft_draw_column(int x, int drawStart, int drawEnd, t_game *game, unsigned int wall)
{
	int y;
	int center;

	center = game->res_height / 2;
	y = 0;
	while ( y < game->res_height)
	{
		if (y < drawStart && y <= center)
			ft_custom_pixel_put(game->img, x, y, game->colors[0]);
		else if (y >= drawStart && y <= drawEnd)
			ft_custom_pixel_put(game->img, x, y, wall);
		else if (y > drawEnd && y > center)
			ft_custom_pixel_put(game->img, x, y, game->colors[1]);
		y++;
	}
}
