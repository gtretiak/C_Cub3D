/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:46:38 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/24 14:43:42 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

int	ft_keypress(int key, t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	printf("Key pressed: %d, moveSpeed=%.4f, rotSpeed=%.4f\n",
        key, game->player->moveSpeed, game->player->rotSpeed);

	if (key == XK_a || key == XK_Left)
	{
		oldDirX = game->player->dirX;
		game->player->dirX = game->player->dirX * cos(game->player->rotSpeed) - game->player->dirY * sin(game->player->rotSpeed);
		game->player->dirY = oldDirX * sin(game->player->rotSpeed) + game->player->dirY * cos(game->player->rotSpeed);
		oldPlaneX = game->player->plnX;
		game->player->plnX = game->player->plnX * cos(game->player->rotSpeed) - game->player->plnY * sin(game->player->rotSpeed);
		game->player->plnY = oldPlaneX * sin(game->player->rotSpeed) + game->player->plnY * cos(game->player->rotSpeed);
	}
	if (key == XK_w || key == XK_Up)
	{
		if(game->map[(int)game->player->posY][(int)(game->player->posX + game->player->dirX * game->player->moveSpeed)] != '1')
			game->player->posX+= game->player->dirX * game->player->moveSpeed;
		if(game->map[(int)(game->player->posY + game->player->dirY * game->player->moveSpeed)][(int)game->player->posX] != '1')
			game->player->posY+= game->player->dirY * game->player->moveSpeed;
	}
	if (key == XK_d || key == XK_Right)
	{
		oldDirX = game->player->dirX;
		game->player->dirX = game->player->dirX * cos(-game->player->rotSpeed) - game->player->dirY * sin(-game->player->rotSpeed);
		game->player->dirY = oldDirX * sin(-game->player->rotSpeed) + game->player->dirY * cos(-game->player->rotSpeed);
		oldPlaneX = game->player->plnX;
		game->player->plnX = game->player->plnX * cos(-game->player->rotSpeed) - game->player->plnY * sin(-game->player->rotSpeed);
		game->player->plnY = oldPlaneX * sin(-game->player->rotSpeed) + game->player->plnY * cos(-game->player->rotSpeed);
	}
	if (key == XK_s || key == XK_Down)
	{

		if(game->map[(int)game->player->posY][(int)(game->player->posX - game->player->dirX * game->player->moveSpeed)] != '1')
			game->player->posX -= game->player->dirX * game->player->moveSpeed;
		if(game->map[(int)(game->player->posY - game->player->dirY * game->player->moveSpeed)][(int)game->player->posX] != '1')
			game->player->posY -= game->player->dirY * game->player->moveSpeed;
	}
	if (key == XK_Escape)
		ft_quit_game();
	return (0);
}
