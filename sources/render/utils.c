/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:48:43 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 15:36:30 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void ft_calc_speed(t_game *game)
{
	double frameTime;
	game->prev_time = game->time;
	game->time = ft_get_current_time();
	frameTime = (game->time - game->prev_time) / 1000.0;

	if((game->time - game->prev_time) < 2)
	{
		game->plyr->moveSpeed = 0.005;
		game->plyr->rotSpeed = 0.003;
		return ;
	}

	game->plyr->moveSpeed = frameTime * 5.0;
	game->plyr->rotSpeed = frameTime * 3.0;
}

int	ft_quit_game(void)
{
	exit(0);
	return (0);
}

double	ft_get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
