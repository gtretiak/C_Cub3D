/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:25:07 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 17:25:09 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	key_movement(int keysym, t_mlx *game) //TODO
{
	/*if (keysym == XK_w)
	       shift_forward;
	else if (keysym == XK_s)
		shift_backward;
	else if (keysym == XK_a)
		shift_left;
	else if (keysym == XK_d)
		shift_right;
	else if (keysym == XK_space) // optional
		jump;
	else if (keysym == XK_Control_L) // optional
		sit_down;*/
	(void)keysym;
	(void)game;
	return (0);
}

int	handle_key(int keysym, t_mlx *game)
{
	if (keysym == XK_Escape
		|| keysym == XK_e || keysym == XK_m) //e - optional, m - bonus
		key_control(keysym, game);
	else if (keysym == XK_w || keysym == XK_s
		|| keysym == XK_a || keysym == XK_d
		|| keysym == XK_space || keysym == XK_Control_L) // optional
		key_movement(keysym, game);
	/*else if (keysym == XK_Left || keysym == XK_Right
		|| keysym == XK_Up || keysym == XK_Down)
		shift_focus; //TODO optional*/
	rendering(game);
	exit(0);
}

int	handle_mouse(int button, int x, int y, t_mlx *game)
{
	(void)x;
	(void)y;
	(void)button;
	(void)game;
	//shift_focus; //TODO bonus
	rendering(game);
	exit(0);
}
