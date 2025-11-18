#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	game;
	t_map	map;
	args_checker(argc, argv);
	file_reading(argv[1], &map);
	init_game(&game);
	rendering(&game);
	mlx_loop(game.mlx);
	exit(0);
}
