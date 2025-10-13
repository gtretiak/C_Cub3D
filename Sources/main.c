#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	game;
	if(argc != 2 || !args_checker(argv[1]))
	{
		ft_printf("Invalid argument\n");
		return 1;
	}

	init(&game);
	rendering(&game);
	mlx_loop(game.mlx);
	exit(0);
}
