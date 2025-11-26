/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:43:06 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/26 11:21:54 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

void init_colors(unsigned int **input, unsigned int *clr_arr)
{
	clr_arr[0] = ((input[0][0] & 0xFF) << 16 | (input[0][1] & 0xFF) << 8 | (input[0][2] & 0xFF));
	clr_arr[1] = ((input[1][0] & 0xFF) << 16 | (input[1][1] & 0xFF) << 8 | (input[1][2] & 0xFF));
}

int is_player(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

void get_xpms(t_game *game, char **textures)
{
	int width;
	int height;

	game->xpms[0] = mlx_xpm_file_to_image(game->mlx_ptr,
		textures[0], &width, &height);
	game->xpms[1] = mlx_xpm_file_to_image(game->mlx_ptr,
		textures[1], &width, &height);
	game->xpms[2] = mlx_xpm_file_to_image(game->mlx_ptr,
		textures[2], &width, &height);
	game->xpms[3] = mlx_xpm_file_to_image(game->mlx_ptr,
		textures[3], &width, &height);
}

void get_player_pos(t_player *plyr, char **map)
{
	int y;
	int x;

	y = 0;
	while(map[y] != NULL)
	{
		x = 0;
		while(map[y][x] != '\0')
		{
			if(is_player(map[y][x]))
			{
				plyr->posX = x + 0.5;
				plyr->posY = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

void init_player(t_game *game, char **map)
{
	game->plyr = malloc(sizeof(t_player));
	if (!game->plyr)
		return;
	get_player_pos(game->plyr, map);
	game->plyr->dirX = -1;
	game->plyr->dirY = 0;
	game->plyr->plnY = 0.66;
	game->plyr->plnX = 0;
	game->plyr->moveSpeed = 0.05;
	game->plyr->rotSpeed = 0.03;
}

void init_mlx(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (ft_printf("mlx_init"), exit(1));
}

void ft_init_struct(t_game *game,char **map, char **textures, unsigned int **colors)
{
	int width;
	int height;
	game->map = map;
	init_mlx(game);
	game->mlx = malloc(sizeof(t_image));
	if(!game->mlx)
		return ;
	init_player(game, map);
	if(!game->plyr)
		return ;
	game->mlx->img_ptr = mlx_new_image(game->mlx_ptr, RESW, RESH);
	game->mlx->img_pixels_ptr = mlx_get_data_addr(game->mlx->img_ptr, &game->mlx->bits_per_pixel, &game->mlx->line_len, &game->mlx->endian);
	game->colors = ft_calloc(2, sizeof(unsigned int));
	if(!game->colors)
		return ;
	init_colors(colors, game->colors);
	game->time = ft_get_current_time();
	game->prev_time = game->time;

	// Initialize all 4 textures
	int i = 0;
	while (i < 4)
	{
		game->textures[i] = ft_calloc(1, sizeof(t_image));
		game->textures[i]->img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, textures[i], &width, &height);
		game->textures[i]->img_pixels_ptr = mlx_get_data_addr(game->textures[i]->img_ptr,
			&game->textures[i]->bits_per_pixel,
			&game->textures[i]->line_len,
			&game->textures[i]->endian);
		i++;
	}
	get_xpms(game, textures);
	game->win_ptr = mlx_new_window(game->mlx_ptr, RESW, RESH, "キュボースリディ");
	// if (!game->win_ptr)
	// 	return (free_game(game), print_error("mlx_new_window"), exit(1));
}
