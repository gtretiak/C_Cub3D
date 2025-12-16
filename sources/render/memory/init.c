/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:43:06 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/16 10:14:23 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../cub3d.h"

void	init_colors(t_scene *scene, unsigned int *clr_arr)
{
	clr_arr[0] = (unsigned int) scene->floor.color;
	clr_arr[1] = (unsigned int) scene->ceilling.color;
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

void	create_texture(char *path, t_game *game, int i)
{
	int	width;
	int	height;

	game->txtr[i] = ft_calloc(1, sizeof(t_image));
	game->txtr[i]->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr,
			path, &width, &height);
	game->txtr[i]->pxl_ptr = mlx_get_data_addr(game->txtr[i]->img_ptr,
			&game->txtr[i]->bpp,
			&game->txtr[i]->line_len,
			&game->txtr[i]->endian);
	free(path);
}

void	init_textures(t_game *game, t_scene *scene)
{
	create_texture(scene->north.path, game, 0);
	create_texture(scene->east.path, game, 1);
	create_texture(scene->south.path, game, 2);
	create_texture(scene->west.path, game, 3);
}

void	ft_init_struct(t_game *game, t_scene *scene)
{
	game->map = scene->map;
	init_mlx(game);
	if (!game->mlx)
		return ;
	ft_init_player(game, scene->map);
	if (!game->plyr)
		return ;
	game->colors = ft_calloc(2, sizeof(unsigned int));
	if (!game->colors)
		return ;
	init_colors(scene, game->colors);
	game->time = ft_get_current_time();
	game->prev_time = game->time;
	init_textures(game, scene);
	if (!game->txtr[0])
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, RESW, RESH, "CUB3D");
	if (!game->win_ptr)
		return ;
}
