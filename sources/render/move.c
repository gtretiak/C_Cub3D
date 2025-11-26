/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:46:38 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 15:35:52 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void	move_y_axis(t_game *game)
{
	double	move_x;
	double	move_y;

	if (game->move_y)
	{
		move_x = game->plyr->dirX * game->plyr->moveSpeed * game->move_y;
		move_y = game->plyr->dirY * game->plyr->moveSpeed * game->move_y;
		if (game->map[(int)game->plyr->posY]
			[(int)(game->plyr->posX + move_x)] != '1')
			game->plyr->posX += move_x;
		if (game->map[(int)(game->plyr->posY + move_y)]
			[(int)game->plyr->posX] != '1')
			game->plyr->posY += move_y;
	}
}

void	move_x_axis(t_game *game)
{
	double	move_x;
	double	move_y;

	if (game->move_x)
	{
		move_x = game->plyr->plnX * game->plyr->moveSpeed * game->move_x;
		move_y = game->plyr->plnY * game->plyr->moveSpeed * game->move_x;
		if (game->map[(int)game->plyr->posY]
			[(int)(game->plyr->posX + move_x)] != '1')
			game->plyr->posX += move_x;
		if (game->map[(int)(game->plyr->posY + move_y)]
			[(int)game->plyr->posX] != '1')
			game->plyr->posY += move_y;
	}
}

void	ft_rotate(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	if (game->rotate)
	{
		if (game->rotate == 1)
			angle = game->plyr->rotSpeed;
		else
			angle = -game->plyr->rotSpeed;
		old_dir_x = game->plyr->dirX;
		game->plyr->dirX = game->plyr->dirX * cos(angle)
			- game->plyr->dirY * sin(angle);
		game->plyr->dirY = (old_dir_x * sin(angle)
				+ game->plyr->dirY * cos(angle));
		old_plane_x = game->plyr->plnX;
		game->plyr->plnX = (game->plyr->plnX * cos(angle)
				- game->plyr->plnY * sin(angle));
		game->plyr->plnY = (old_plane_x * sin(angle)
				+ game->plyr->plnY * cos(angle));
	}
}

void	ft_handle_movement(t_game *game)
{
	if (game->move_y)
		move_y_axis(game);
	if (game->move_x)
		move_x_axis(game);
}
