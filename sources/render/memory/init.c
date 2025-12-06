/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:43:06 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 12:05:43 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../render.h"

void	init_colors(unsigned int **input, unsigned int *clr_arr)
{
	clr_arr[0] = ((input[0][0] & 0xFF) << 16
			| (input[0][1] & 0xFF) << 8 | (input[0][2] & 0xFF));
	clr_arr[1] = ((input[1][0] & 0xFF) << 16
			| (input[1][1] & 0xFF) << 8 | (input[1][2] & 0xFF));
}

void	init_mlx(t_game *game)
{
	game->mlx = malloc(sizeof(t_image));
	if (!game->mlx)
		return ;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_printf("mlx_init"), exit(1));
	game->mlx->img_ptr = mlx_new_image(game->mlx_ptr, RESW, RESH);
	game->mlx->pxl_ptr = mlx_get_data_addr(game->mlx->img_ptr,
			&game->mlx->bpp, &game->mlx->line_len,
			&game->mlx->endian);
}

void	init_textures(t_game *game, char **textures)
{
	int	width;
	int	height;
	int	i;

	i = 0;
	while (i < 4)
	{
		game->txtr[i] = ft_calloc(1, sizeof(t_image));
		game->txtr[i]->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
				textures[i], &width, &height);
		game->txtr[i]->pxl_ptr = mlx_get_data_addr(game->txtr[i]->img_ptr,
				&game->txtr[i]->bpp,
				&game->txtr[i]->line_len,
				&game->txtr[i]->endian);
		i++;
	}
}

void	ft_init_struct(t_game *game, char **map,
	char **textures, unsigned int **colors)
{
	game->map = map;
	init_mlx(game);
	if (!game->mlx)
		return ;
	ft_init_player(game, map);
	if (!game->plyr)
		return ;
	game->colors = ft_calloc(2, sizeof(unsigned int));
	if (!game->colors)
		return ;
	init_colors(colors, game->colors);
	game->time = ft_get_current_time();
	game->prev_time = game->time;
	init_textures(game, textures);
	if (!game->txtr[0])
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, RESW, RESH, "キュボースリディ");
	if (!game->win_ptr)
		return ;
}
