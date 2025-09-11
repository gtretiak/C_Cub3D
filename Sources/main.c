#include "cub3d.h"

int	main(void)
{
	t_mlx	game;

	init(&game);
	rendering(&game);
	mlx_loop(game.mlx);
	exit(0);
}
