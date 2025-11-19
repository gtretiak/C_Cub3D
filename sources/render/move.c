/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:46:38 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/19 16:03:25 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

// int	ft_keypress(int key, t_game *game)
int	ft_keypress(int key)
{
	if (key == XK_a || key == XK_Left)
		// player_move('l', game);
	if (key == XK_w || key == XK_Up)
		// player_move('u', game);
	if (key == XK_d || key == XK_Right)
		// player_move('r', game);
	if (key == XK_s || key == XK_Down)
		// player_move('d', game);
	if (key == XK_Escape)
		// ft_quit_game(game);
		ft_quit_game();
	return (0);
}
