/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:52:17 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 12:03:33 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

int raycasting(t_game *game)
{
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
	while(x < RESW)
	{
		cameraX = 2 * x / (double) RESW - 1;

		rayDirX = game->plyr->dirX + game->plyr->plnX * cameraX;
		rayDirY = game->plyr->dirY + game->plyr->plnY * cameraX;

		mapX = (int)game->plyr->posX;
		mapY = (int)game->plyr->posY;

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
			sideDistX = (game->plyr->posX - mapX) * deltaDistX;
		} else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->plyr->posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->plyr->posY - mapY) * deltaDistY;
		} else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->plyr->posY) * deltaDistY;
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

		lineHeight = (int) (RESH / perpWallDist);

		drawStart = -lineHeight / 2 + RESH / 2;
		if(drawStart < 0)
			drawStart = 0;

		drawEnd = lineHeight / 2 + RESH / 2;
		if(drawEnd >= RESH)
			drawEnd = RESH - 1;

		int texnum = game->map[mapY][mapX] - '1';
		double wallX;

		if(side == 0)
			wallX = game->plyr->posY + perpWallDist * rayDirY;
		else
			wallX = game->plyr->posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));		int texX = (int)(wallX * (double)64);

		if(side == 0 && rayDirX > 0)
			texX = 64 - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = 64 - texX - 1;


		// draw texture
		double step = 1.0 * 64 / lineHeight;
		double texPos = (drawStart - RESH / 2 + lineHeight) * step;
		int y = drawStart;

		//draw colors
		int y2 = 0;
		while (y2 <= RESH)
		{
			if (y2 < drawStart)
				ft_custom_pixel_put(game->mlx, x, y2, game->colors[0]);
			else if (y2 > drawEnd)
				ft_custom_pixel_put(game->mlx, x, y2, game->colors[1]);
			y2++;
		}

		while (y <= drawEnd)
		{
			int texY = (int) texPos & (64 - 1);
			texPos += step;
			int offset = (game->txtr[texnum]->line_len * texY) + (texX * (game->txtr[texnum]->bpp / 8));
			unsigned int color = *(unsigned int *)(game->txtr[texnum]->pxl_ptr + offset);



			ft_custom_pixel_put(game->mlx, x, y, color);
			y++;
		}
		ft_calc_speed(game);
		x++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->mlx->img_ptr, 0, 0);
	return 0;
}

void ft_render(char **map, char **textures, unsigned int **colors)
{
	t_game game;

	ft_bzero(&game, sizeof(t_game));
	ft_init_struct(&game, map, textures, colors);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &ft_keypress, &game);
	mlx_hook(game.win_ptr, DestroyNotify,
		StructureNotifyMask, &ft_quit_game, &game);
	mlx_loop_hook(game.mlx_ptr, raycasting, &game);
	mlx_loop(game.mlx_ptr);
}

int main(void)
{
	//! testing vars
	unsigned int color_top[] = {75, 75, 75};
    unsigned int color_bot[] = {50, 50, 255};
    unsigned int *colors[] = {color_top, color_bot};
	char *textures[] = {"./a.xpm","./wall.xpm","./a.xpm","./wall.xpm"};
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


	ft_render(map, textures, colors);
	return 0;
}
