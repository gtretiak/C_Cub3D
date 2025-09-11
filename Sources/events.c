#include "cub3d.h"

int	handle_closing(t_mlx *game)
{
	mlx_destroy_image(game->mlx, game->img.img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	handle_key(int keysym, t_mlx *game)
{
	if (keysym ==XK_Escape)
		handle_closing(game);
	rendering(game);
	exit(0);
}

int	handle_mouse(int button, int x, int y, t_mlx *game)
{
	(void)x;
	(void)y;
	(void)button;
	(void)game;
	rendering(game);
	exit(0);
}
