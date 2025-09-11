#include "cub3d.h"


void	put_pixels(int x, int y, t_img *img, int color)
{
	int	offset;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	offset = (img->line_len * y) + (x * img->bpp / 8);
	*((unsigned int *)(img->pixels + offset)) = color;
}

void	rendering(t_mlx *game)
{
	int	x;
	int	y;

	y = 0;
	while (y++ < HEIGHT)
	{
		x = 0;
		while (x++ < WIDTH)
			put_pixels(x, y, &game->img, 777);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
