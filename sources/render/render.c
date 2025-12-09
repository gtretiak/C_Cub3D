/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:31:25 by rimagalh          #+#    #+#             */
/*   Updated: 2025/12/09 10:04:56 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

// void	ft_render(char **map, char **textures, unsigned int **colors)
void	ft_render(t_scene* scene)
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

// int main(void)
// {
// 	unsigned int	color_bot[] = {75, 75, 75};
//     unsigned int	color_top[] = {50, 50, 255};
//     unsigned int	*colors[] = {color_bot, color_top};
// 	char			*textures[] = {"./n.xpm","./e.xpm","./s.xpm","./w.xpm"};
// 	char			*map[] = {
// 		"1111111111111111111111111",
// 		"1000000000110000000000001",
// 		"1011000001110000000000001",
// 		"1001000000000000000000001",
// 		"1111111110110000011100001",
// 		"1000000000110000011101111",
// 		"1111011111111101110000001",
// 		"1111011111111101110101001",
// 		"1100000011010101110000001",
// 		"1000000000000000110000001",
// 		"1000000000000000110101001",
// 		"11000001110101011110E0111",
// 		"11110111 1110101 10111101",
// 		"11111111 1111111 11111111",
// 		NULL
// 	};
// 	ft_render(map, textures, colors);
// 	return 0;
// }
