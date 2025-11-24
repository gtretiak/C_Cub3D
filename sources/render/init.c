/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:43:06 by rimagalh          #+#    #+#             */
/*   Updated: 2025/11/24 14:13:50 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./render.h"

//* typedef struct s_player
//* {
//* 	double posX;
//* 	double posY;
//* 	double dirX;
//* 	double dirY;
//* 	double camX;
//* 	double camY;
//* }	t_player;

void init_colors(unsigned int **input, unsigned int *clr_arr)
{
	clr_arr[0] = ((input[0][0] & 0xFF) << 16 | (input[0][1] & 0xFF) << 8 | (input[0][2] & 0xFF));
	clr_arr[1] = ((input[1][0] & 0xFF) << 16 | (input[1][1] & 0xFF) << 8 | (input[1][2] & 0xFF));
}

int is_player(char c)
{
	if (c == 'N')
		return (0);
	if (c == 'E')
		return (90);
	if (c == 'S')
		return (180);
	if (c == 'W')
		return (270);

	return (-1);
}

void init_player(t_player *player, char **map)
{
	int y;
	int x;

	y = 0;
	while(map[y] != NULL)
	{
		x = 0;
		while(map[y][x] != '\0')
		{
			if(is_player(map[y][x]) != -1)
			{
				player->posX = x + 0.5;
				player->posY = y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

void init_map_size(int *height, int *width, char **map)
{
	int i;
	size_t max;

	i = 0;
	max = 0;
	while(map[i] != NULL)
	{
		if(ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	*height = i;
	*width = (int)max;
}

//* typedef struct s_game
//* {
//* 	char	**map;
//* 	int		res_height;
//* 	int		res_width;
//* 	int		map_width;
//* 	int		map_height;
//* 	double time;
//* 	double prev_time;
//* 	t_player *player;
//* }	t_game;

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

void ft_init_game(t_game *game,char **map, char **textures, unsigned int **colors)
{
	game->mlx_ptr = mlx_init();
	// if (!game->mlx_ptr)
	// 	return (free_game(game), print_error("mlx_init"), exit(1));
	game->map = map;
	game->res_width = 1280 / 2;
	game->res_height = 720 / 2;
	game->player = ft_calloc(1, sizeof(t_player));
	if(!game->player)
		return ;
	game->img = ft_calloc(1, sizeof(t_image));
	if(!game->img)
		return ;

	init_player(game->player, map);
	// if(!game->player)
	// 	return ;
	game->img->img_ptr = mlx_new_image(game->mlx_ptr, game->res_width, game->res_height);
	game->img->img_pixels_ptr = mlx_get_data_addr(game->img->img_ptr, &game->img->bits_per_pixel, &game->img->line_len, &game->img->endian);
	game->colors = ft_calloc(2, sizeof(unsigned int));
	if(!game->colors)
		return ;
	init_colors(colors, game->colors);
	game->player->dirX = -1;
	game->player->dirY = 0;
	game->player->plnY = 0.66;
	game->player->plnX = 0;
	get_xpms(game, textures);
	init_map_size(&game->map_height, &game->map_width, map);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->res_width, game->res_height, "キュボースリディ");
	// if (!game->win_ptr)
	// 	return (free_game(game), print_error("mlx_new_window"), exit(1));
}
