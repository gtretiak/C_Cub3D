#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	game;
	t_scene	scene;
	args_checker(argc, argv); // comment for debugging
//	(void)argc; // uncomment for debugging
	file_reading(argv[1], &scene);
	init_game(&game);
	rendering(&game);
	mlx_loop(game.mlx);
	exit(0);
}
