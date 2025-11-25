/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 13:52:17 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/25 11:36:49 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

// void ft_calc_speed(t_game *game)
// {
// 	double frameTime;
// 	game->prev_time = game->time;
// 	game->time = ft_get_current_time();
// 	frameTime = (game->time - game->prev_time) / 1000.0;

// 	if((game->time - game->prev_time) < 2)
// 	{
// 		game->player->moveSpeed = 0.05;
// 		game->player->rotSpeed = 0.03;
// 		return ;
// 	}

// 	game->player->moveSpeed = frameTime * 5.0;
// 	game->player->rotSpeed = frameTime * 3.0;
// 	printf("calc_speed: prev=%.0f, time=%.0f, frameTime=%.4f, moveSpeed=%.4f\n",
// 		game->prev_time, game->time, frameTime, game->player->moveSpeed);
// }

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

		int texnum = game->map[mapY][mapX] - '1';
		double wallX;

		if(side == 0)
			wallX = game->player->posY + perpWallDist * rayDirY;
		else
			wallX = game->player->posY + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int texX = (int)(wallX * (double)64);

		if(side == 0 && rayDirX > 0)
			texX = 64 - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = 64 - texX - 1;

		double step = 1.0 * 64 / lineHeight;
		double texPos = (drawStart - game->res_height / 2 + lineHeight) * step;
		int y = drawStart;

		while (y <= drawEnd)
		{
			int texY = (int) texPos & (64 - 1);
			texPos += step;
			int offset = (game->textures[texnum]->line_len * texY) + (texX * (game->textures[texnum]->bits_per_pixel / 8));
			unsigned int color = *(unsigned int *)(game->textures[texnum]->img_pixels_ptr + offset);
			if(side == 1)
				color = (color >> 1) & 8355711;
			ft_custom_pixel_put(game->img, x, y, color);
			y++;
		}
		// ft_calc_speed(game);
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
	char *textures[] = {"./a.xpm","./wall.xpm","./a.xpm","./a.xpm"};
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
	mlx_loop_hook(game.mlx_ptr, raycasting, &game);
	mlx_loop(game.mlx_ptr);
	return 0;
}
