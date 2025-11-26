/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:46:38 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 14:44:53 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

int	ft_keypress(int key, t_game *game)
{
	double oldDirX;
	double oldPlaneX;

	if (key == XK_w || key == XK_Up)
	{
		if(game->map[(int)game->plyr->posY][(int)(game->plyr->posX + game->plyr->dirX * game->plyr->moveSpeed)] != '1')
		game->plyr->posX+= game->plyr->dirX * game->plyr->moveSpeed;
		if(game->map[(int)(game->plyr->posY + game->plyr->dirY * game->plyr->moveSpeed)][(int)game->plyr->posX] != '1')
		game->plyr->posY+= game->plyr->dirY * game->plyr->moveSpeed;
	}
	if (key == XK_s || key == XK_Down)
	{

		if(game->map[(int)game->plyr->posY][(int)(game->plyr->posX - game->plyr->dirX * game->plyr->moveSpeed)] != '1')
			game->plyr->posX -= game->plyr->dirX * game->plyr->moveSpeed;
		if(game->map[(int)(game->plyr->posY - game->plyr->dirY * game->plyr->moveSpeed)][(int)game->plyr->posX] != '1')
			game->plyr->posY -= game->plyr->dirY * game->plyr->moveSpeed;
	}
	if(key == XK_Left)
	{
		oldDirX = game->plyr->dirX;
		game->plyr->dirX = game->plyr->dirX * cos(-game->plyr->rotSpeed) - game->plyr->dirY * sin(-game->plyr->rotSpeed);
		game->plyr->dirY = oldDirX * sin(-game->plyr->rotSpeed) + game->plyr->dirY * cos(-game->plyr->rotSpeed);
		oldPlaneX = game->plyr->plnX;
		game->plyr->plnX = game->plyr->plnX * cos(-game->plyr->rotSpeed) - game->plyr->plnY * sin(-game->plyr->rotSpeed);
		game->plyr->plnY = oldPlaneX * sin(-game->plyr->rotSpeed) + game->plyr->plnY * cos(-game->plyr->rotSpeed);
	}
	if(key == XK_Right)
	{
		oldDirX = game->plyr->dirX;
		game->plyr->dirX = game->plyr->dirX * cos(game->plyr->rotSpeed) - game->plyr->dirY * sin(game->plyr->rotSpeed);
		game->plyr->dirY = oldDirX * sin(game->plyr->rotSpeed) + game->plyr->dirY * cos(game->plyr->rotSpeed);
		oldPlaneX = game->plyr->plnX;
		game->plyr->plnX = game->plyr->plnX * cos(game->plyr->rotSpeed) - game->plyr->plnY * sin(game->plyr->rotSpeed);
		game->plyr->plnY = oldPlaneX * sin(game->plyr->rotSpeed) + game->plyr->plnY * cos(game->plyr->rotSpeed);
	}
	if(key == XK_a)
	{
		if(game->map[(int)game->plyr->posY][(int)(game->plyr->posX - game->plyr->plnX * game->plyr->moveSpeed)] != '1')
        	game->plyr->posX -= game->plyr->plnX * game->plyr->moveSpeed;
    	if(game->map[(int)(game->plyr->posY - game->plyr->plnY * game->plyr->moveSpeed)][(int)game->plyr->posX] != '1')
        	game->plyr->posY -= game->plyr->plnY * game->plyr->moveSpeed;
	}
	if(key == XK_d)
	{
		if(game->map[(int)game->plyr->posY][(int)(game->plyr->posX + game->plyr->plnX * game->plyr->moveSpeed)] != '1')
			game->plyr->posX += game->plyr->plnX * game->plyr->moveSpeed;
		if(game->map[(int)(game->plyr->posY + game->plyr->plnY * game->plyr->moveSpeed)][(int)game->plyr->posX] != '1')
			game->plyr->posY += game->plyr->plnY * game->plyr->moveSpeed;
	}
	if (key == XK_Escape)
		ft_quit_game();
	return (0);
}
