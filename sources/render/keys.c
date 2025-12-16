/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:10:43 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/16 10:14:47 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_keyrelease(int key, t_game *game)
{
	if (key == XK_w || key == XK_Up || key == XK_s || key == XK_Down)
		game->move_y = 0;
	if (key == XK_Right || key == XK_Left)
		game->rotate = 0;
	if (key == XK_d || key == XK_a)
		game->move_x = 0;
	return (0);
}

int	ft_keypress(int key, t_game *game)
{
	if (key == XK_w || key == XK_Up)
		game->move_y = 1;
	if (key == XK_s || key == XK_Down)
		game->move_y = -1;
	if (key == XK_Right)
		game->rotate = 1;
	if (key == XK_Left)
		game->rotate = -1;
	if (key == XK_d)
		game->move_x = 1;
	if (key == XK_a)
		game->move_x = -1;
	if (key == XK_Escape)
		ft_quit_game(game);
	return (0);
}
