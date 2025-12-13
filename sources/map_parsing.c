/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:28:29 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/12 14:25:20 by rimagalh         ###   ########.fr       */
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
// 	*ft_strchr(scene->map[scene->map_row], '\0') = line[i];//Do I need it?
// 	if line[i] = '\n', then my scene->map line isn't terminated?

/* static int	flood_fill(t_scene *scene, int row, int col)
{
	if (row < 0 || row >= scene->map_size.y
		|| col < 0 || col >= (int)ft_strlen(scene->map[row]))
		return (0);
	if (scene->map[row][col] == '1' || scene->map[row][col] == 'f'
		|| scene->map[row][col] == scene->player.direction)
		return (0);
	if (scene->map[row][col] != '0' && scene->map[row][col] != 'f'
		&& scene->map[row][col] != '1')
		return (1);
	if (scene->map[row][col] == '0')
		scene->map[row][col] = 'f';
	flood_fill(scene, row - 1, col);
	flood_fill(scene, row + 1, col);
	flood_fill(scene, row, col + 1);
	flood_fill(scene, row, col - 1);
	return (0);
}*/
/*
static int	flood_fill(t_scene *scene, int row, int col)
{
	char current;
	int line_len;

	//out of bounds vertically
	if(row < 0 || row >= scene->map_size.y)
		return (0);
	line_len = (int)ft_strlen(scene->map[row]);
	//out of bounds horizontally
	if(col < 0 || col >= line_len)
	{
		// If trying to go beyond the line, check the last character
		// If last char is not a wall, it's a hole
		if (line_len > 0 && col == line_len)
		{
			char last_char = scene->map[row][line_len - 1];
			if (last_char != '1')
				return (1); //line ends without wall
		}
		return (0); // Out of bounds but line ends with wall
	}
	current = scene->map[row][col];

	//already visited
	if(current == 'f')
		return (0);
	//wall is the valid boundary so stop
	if(current == '1')
		return (0);
	//by this point it could only be a 0 or the player
	//so if it isnt, error
	if (current != '0' && current != scene->player.direction)
		return (1);
	//if every if passes that means its a 0 or player
	//if its a 0 make it an F
	//never replace the player since rendering depends on it
	else if (current == '0')
		scene->map[row][col] = 'f';
	//needs the return to propagate errors just like the first call
	//otherwise it would always return 0 regardless
	//because that's the default return value
	if(flood_fill(scene, row - 1, col))
		return (1);
	if(flood_fill(scene, row + 1, col))
		return (1);
	if(flood_fill(scene, row, col - 1))
		return (1);
	if(flood_fill(scene, row, col + 1))
		return (1);
	return (0);
}
*/
static int	flood_fill(t_scene *scene, int row, int col)
{
	char current;
	int line_len;

	//out of bounds vertically
	if(row < 0 || row >= scene->map_size.y)
		return (1); // a typo? should be 1 (not 0)?
	if (!scene->map[row])
		return (1);
	line_len = (int)ft_strlen(scene->map[row]);
	//out of bounds horizontally v.2.0
	if (col < 0 || col >= line_len)
		return (1); //line ends without wall
	current = scene->map[row][col];
	//already visited
	if(current == 'f')
		return (0);
	//wall is the valid boundary so stop
	if(current == '1')
		return (0);
	//by this point it could only be a 0 or the player
	//so if it isnt, error
	if (ft_isspace(current))
		scene->map[row][col] = 'f';
	//if every if passes that means its a 0 or player
	//if its a 0 make it an F
	//never replace the player since rendering depends on it
	else if (current == '0')
		scene->map[row][col] = 'f';
	else if (current != scene->player.direction)
		return (1);
	//needs the return to propagate errors just like the first call
	//otherwise it would always return 0 regardless
	//because that's the default return value
	if(flood_fill(scene, row - 1, col))
		return (1);
	if(flood_fill(scene, row + 1, col))
		return (1);
	if(flood_fill(scene, row, col - 1))
		return (1);
	if(flood_fill(scene, row, col + 1))
		return (1);
	return (0);
}

void	parse_map(int fd, t_scene *scene)
{
	if (flood_fill(scene, scene->player.point.y, scene->player.point.x))
	{
		free_scene(scene);
		close(fd);
		exiter(MAP_WALLS); // replace with return logic?
	}
}
