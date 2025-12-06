/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:27:17 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 18:08:11 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	game;
	t_scene	scene;

	args_checker(argc, argv);
	file_reading(argv[1], &scene);
	init_game(&game, &scene);
	rendering(&game);
	mlx_loop(game.mlx);
	exit(0);
}
