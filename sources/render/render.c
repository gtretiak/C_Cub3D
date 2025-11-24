/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:52:17 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/24 11:56:11 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

int raycasting(t_game *game)
{
	unsigned int wall;
	int x;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int mapY;
	int mapX;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;

	x = 0;
	while(x < game->res_width)
	{
		cameraX = 2 * x / (double) game->res_width - 1;

		rayDirX = game->player->dirX + game->player->plnX * cameraX;
		rayDirY = game->player->dirY + game->player->plnY * cameraX;

		mapX = (int)game->player->posX;
		mapY = (int)game->player->posY;

		hit = 0;

		if(rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1/rayDirX);

		if(rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1/rayDirY);

		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->posX - mapX) * deltaDistX;
		} else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->posY - mapY) * deltaDistY;
		} else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->posY) * deltaDistY;
		}


		while(hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(game->map[mapY][mapX] == '1')
				hit = 1;
		}

		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		lineHeight = (int) (game->res_height / perpWallDist);

		drawStart = -lineHeight / 2 + game->res_height / 2;
		if(drawStart < 0)
			drawStart = 0;

		drawEnd = lineHeight / 2 + game->res_height / 2;
		if(drawEnd >= game->res_height)
			drawEnd = game->res_height - 1;

		if(side == 1)
			wall = 0xFFFF00;
		else
			wall = 0x7F7F00;
		printf("mapX=%d mapY=%d posX=%f posY=%f\n", mapX, mapY, game->player->posX, game->player->posY);
		ft_draw_column(x, drawStart, drawEnd, game, wall);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img->img_ptr, 0, 0);
	return 0;
}

// int ft_render(char **map, char **textures, unsigned int **colors)
int main(void)
{
	t_game game;
	unsigned int color_top[] = {75, 75, 75};
    unsigned int color_bot[] = {50, 50, 255};
    unsigned int *colors[] = {color_top, color_bot};
	char *textures[] = {"./a.xpm","./a.xpm","./a.xpm","./a.xpm"};
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
	ft_init_game(&game, map, textures, colors);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &ft_keypress, &game);
	mlx_hook(game.win_ptr, DestroyNotify,
		StructureNotifyMask, &ft_quit_game, &game);
	// render_game(&game);
	// raycasting(&game);
	mlx_loop_hook(game.mlx_ptr, raycasting, &game);
	mlx_loop(game.mlx_ptr);
	return 0;
}
