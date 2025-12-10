/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:31:25 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/10 11:22:49 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void	ft_render(t_scene *scene)
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	ft_init_struct(&game, scene);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &ft_keypress, &game);
	mlx_hook(game.win_ptr, KeyRelease, KeyReleaseMask, &ft_keyrelease, &game);
	mlx_hook(game.win_ptr, DestroyNotify,
		StructureNotifyMask, &ft_quit_game, &game);
	mlx_loop_hook(game.mlx_ptr, ft_raycast, &game);
	mlx_loop(game.mlx_ptr);
}
