/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_other.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:25:46 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 17:25:47 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	handle_closing(t_mlx *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	handle_action(t_mlx *game) //TODO
{
	(void)game;
	return (0);
}

int	handle_mini(t_mlx *game) //TODO
{
	(void)game;
	return (0);
}

int	key_control(int keysym, t_mlx *game)
{
	if (keysym == XK_Escape)
		handle_closing(game);
	if (keysym == XK_e)
		handle_action(game); //TODO
	if (keysym == XK_m)
		handle_mini(game); //TODO
	(void)keysym;
	(void)game;
	return (0);
}
