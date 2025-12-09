/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:26:43 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/09 11:06:39 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub3d.h"

// void	event_listening(t_mlx *game)
// {
// 	mlx_hook(game->win, KeyPress, KeyPressMask, handle_key, game);
// 	mlx_mouse_hook(game->win, handle_mouse, game);
// 	mlx_hook(game->win, DestroyNotify, StructureNotifyMask,
// 		handle_closing, game);
// }

// void	init_game(t_mlx *game, t_scene *scene)
// {
// 	game->mlx = mlx_init();
// 	if (!game->mlx)
// 		malloc_error(scene);
// 	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Cub3D");
// 	if (!game->win)
// 	{
// 		mlx_destroy_display(game->mlx);
// 		free(game->mlx);
// 		malloc_error(scene);
// 	}
// 	game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	if (!game->img.img)
// 	{
// 		mlx_destroy_window(game->mlx, game->win);
// 		mlx_destroy_display(game->mlx);
// 		free(game->mlx);
// 		malloc_error(scene);
// 	}
// 	game->img.pixels = mlx_get_data_addr(game->img.img, &game->img.bpp,
// 			&game->img.line_len, &game->img.endian);
// 	event_listening(game);
// }
