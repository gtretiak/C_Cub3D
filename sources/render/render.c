/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:52:17 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/19 16:13:53 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"



// int ft_render(char **map, char **textures)
int main(void)
{
	t_game game;
	char *textures[] = {"Path/To/N","Path/To/E","Path/To/S","Path/To/W"};
	char *map[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011000001110000000000001",
		"1001000000000000000000001",
		"1111111110110000011100001",
		"1000000000110000011101111",
		"1111011111111101110000001",
		"1111011111111101110101001",
		"1100000011010101110000001",
		"1000000000000000110000001",
		"1000000000000000110101001",
		"11000001110101011110N0111",
		"11110111 1110101 10111101",
		"11111111 1111111 11111111",
		NULL
	};
	ft_bzero(&game, sizeof(t_game));
	ft_init_game(&game, map, textures);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &ft_keypress, &game);
	mlx_hook(game.win_ptr, DestroyNotify,
		StructureNotifyMask, &ft_quit_game, &game);
	// render_game(&game);
	mlx_loop(game.mlx_ptr);
	return 0;
}
