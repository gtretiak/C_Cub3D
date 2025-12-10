/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:48:43 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/10 15:05:58 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void	ft_calc_speed(t_game *game)
{
	double	frametime;

	game->prev_time = game->time;
	game->time = ft_get_current_time();
	frametime = (game->time - game->prev_time) / 1000.0;
	if (frametime < 0.001 || frametime > 1.0)
	{
		game->plyr->move_speed = 0.10;
		game->plyr->rot_speed = 0.06;
		return ;
	}
	game->plyr->move_speed = frametime * 5.0;
	game->plyr->rot_speed = frametime * 3.0;
}

int	ft_quit_game(t_game *game)
{
	ft_free_game(game);
	exit(0);
	return (0);
}

void	print_exit(char *err, t_game *game)
{
	ft_printf("%s failed", err);
	ft_free_game(game);
	exit(1);
}

double	ft_get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
