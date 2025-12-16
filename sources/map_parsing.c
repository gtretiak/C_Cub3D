/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:28:29 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/16 10:31:21 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	handle_player(t_scene *scene, char c, int i)
{
	if (scene->player.on_position)
		return (returner(MAP_PLAYER));
	scene->player.direction = c;
	scene->player.point.x = i;
	scene->player.point.y = scene->map_row;
	scene->player.on_position = true;
	return (0);
}

static int	char_processing(char c, t_scene *scene, int i)
{
	if (ft_isspace(c) || c == '1' || c == '0')
		return (0);
	else if (c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (handle_player(scene, c, i));
	return (returner(MAP_UNEXPECTED));
}

int	build_map(char *line, t_scene *scene)
{
	int		i;
	int		l;
	char	*last_char_ptr;

	i = 0;
	if (scene->flag >= 0)
		scene->flag = 1;
	else
		return(returner(MAP_LAST));
	if (scene->map_row >= scene->map_size.y)
		return(returner(MAP_INV));
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (char_processing(line[i], scene, i))
			return (1);
		i++;
	}
	l = ft_strlen(line);
	if (l > scene->map_size.x)
		scene->map_size.x = l;
	scene->map[scene->map_row] = ft_strdup(line);
	if (!scene->map[scene->map_row])
		malloc_error(scene);
	last_char_ptr = ft_strchr(scene->map[scene->map_row], '\n');
	if (last_char_ptr)
		*last_char_ptr = '\0';
	scene->map_row++;
	return (0);
}

static int	flood_fill(t_scene *scene, int row, int col)
{
	char	current;

	if (row < 0 || row >= scene->map_size.y)
		return (1);
	if (!scene->map[row])
		return (1);
	if (col < 0 || col >= (int)ft_strlen(scene->map[row]))
		return (1);
	current = scene->map[row][col];
	if (current == 'f' || current == '1')
		return (0);
	if (current == '0')
		scene->map[row][col] = 'f';
	else if (current != scene->player.direction)
		return (1);
	if (flood_fill(scene, row - 1, col))
		return (1);
	if (flood_fill(scene, row + 1, col))
		return (1);
	if (flood_fill(scene, row, col - 1))
		return (1);
	if (flood_fill(scene, row, col + 1))
		return (1);
	return (0);
}

void	parse_map(int fd, t_scene *scene)
{
	if (flood_fill(scene, scene->player.point.y, scene->player.point.x))
	{
		free_scene(scene);
		close(fd);
		exiter(MAP_WALLS);
	}
}
