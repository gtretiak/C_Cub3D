/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:11:13 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/10 11:24:39 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h"

void	ft_free_arr(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->txtr[i])
		{
			if (game->txtr[i]->img_ptr && game->mlx_ptr)
				mlx_destroy_image(game->mlx_ptr, game->txtr[i]->img_ptr);
			free(game->txtr[i]);
		}
		i++;
	}
}

void	ft_free_game(t_game *game)
{
	if (!game)
		return ;
	// if (game->map)
	// 	ft_free_arr((void **)game->map);
	if (game->plyr)
		free(game->plyr);
	if (game->mlx)
	{
		if (game->mlx->img_ptr && game->mlx_ptr)
			mlx_destroy_image(game->mlx_ptr, game->mlx->img_ptr);
		free(game->mlx);
	}
	free_textures(game);
	if (game->colors)
		free(game->colors);
	if (game->win_ptr && game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
