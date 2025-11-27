/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:46:38 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/27 11:54:50 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void	move_y_axis(t_game *game)
{
	double	move_x;
	double	move_y;

	if (game->move_y)
	{
		move_x = game->plyr->dir_x * game->plyr->move_speed * game->move_y;
		move_y = game->plyr->dir_y * game->plyr->move_speed * game->move_y;
		if (game->map[(int)game->plyr->pos_y]
			[(int)(game->plyr->pos_x + move_x)] != '1')
			game->plyr->pos_x += move_x;
		if (game->map[(int)(game->plyr->pos_y + move_y)]
			[(int)game->plyr->pos_x] != '1')
			game->plyr->pos_y += move_y;
	}
}

void	move_x_axis(t_game *game)
{
	double	move_x;
	double	move_y;

	if (game->move_x)
	{
		move_x = game->plyr->plane_x * game->plyr->move_speed * game->move_x;
		move_y = game->plyr->plane_y * game->plyr->move_speed * game->move_x;
		if (game->map[(int)game->plyr->pos_y]
			[(int)(game->plyr->pos_x + move_x)] != '1')
			game->plyr->pos_x += move_x;
		if (game->map[(int)(game->plyr->pos_y + move_y)]
			[(int)game->plyr->pos_x] != '1')
			game->plyr->pos_y += move_y;
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
			angle = game->plyr->rot_speed;
		else
			angle = -game->plyr->rot_speed;
		old_dir_x = game->plyr->dir_x;
		game->plyr->dir_x = game->plyr->dir_x * cos(angle)
			- game->plyr->dir_y * sin(angle);
		game->plyr->dir_y = (old_dir_x * sin(angle)
				+ game->plyr->dir_y * cos(angle));
		old_plane_x = game->plyr->plane_x;
		game->plyr->plane_x = (game->plyr->plane_x * cos(angle)
				- game->plyr->plane_y * sin(angle));
		game->plyr->plane_y = (old_plane_x * sin(angle)
				+ game->plyr->plane_y * cos(angle));
	}
}

void	ft_handle_movement(t_game *game)
{
	if (game->move_y)
		move_y_axis(game);
	if (game->move_x)
		move_x_axis(game);
}
