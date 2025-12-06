/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:53:49 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 17:10:15 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	identifiers_or_weird(char *line, t_scene *scene)
{
	if (line[0] == 'F' || line[0] == 'C')
		return (set_flat(line, scene));
	if ((line[0] == 'N') || (line[0] == 'S')
		|| (line[0] == 'W') || (line[0] == 'E'))
		return (define_wall(line, scene));
	if (scene->flag == 1)
		return (returner(MAP_UNEXPECTED));
	return (returner(ELEMENT_UNEXPECTED));
}

static int	parse_scene(char *line, t_scene *scene)
{
	short	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '1' || line[i] == '0')
			return (build_map(line, scene));
		if (ft_isspace(line[i]))
		{
			if (scene->flag == 0 || scene->flag == 1)
				return (build_map(line, scene));
			continue ;
		}
		if (line[i] == '\n')
		{
			if (scene->flag == 1)
				return (returner(MAP_GAPS));
			return (0);
		}
		return (identifiers_or_weird(line, scene));
	}
	return (0);
}

static int	reached_eof(int fd, t_scene *scene)
{
	char	*str;

	str = get_next_line(fd, 0);
	if (!str)
		return (1);
	if (parse_scene(str, scene))
	{
		free(str);
		str = get_next_line(fd, 2);
		free(str);
		free_scene(scene);
		close(fd);
		exit(1);
	}
	free(str);
	return (0);
}
// PS: 0 means usual flow, whereas 2 means freeing static tmp

static void	check_for_missing(int fd, t_scene *scene)
{
	bool	error;
	char	*output;

	error = true;
	if (scene->flag != 1)
		output = MAP_NO;
	else if (!scene->player.on_position)
		output = MAP_NO_PLAYER;
	else if (!scene->floor.installed)
		output = MAP_NO_FLOOR;
	else if (!scene->ceilling.installed)
		output = MAP_NO_CEILLING;
	else if (!scene->north.installed || !scene->south.installed
		|| !scene->west.installed || !scene->east.installed)
		output = MAP_NO_WALL;
	else
		error = false;
	if (!error)
		return ;
	free_scene(scene);
	close(fd);
	exiter(output);
}

int	file_reading(char *file, t_scene *scene)
{
	int		fd;

	init_scene(file, scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	while (!reached_eof(fd, scene))
		;
	check_for_missing(fd, scene);
	parse_map(fd, scene);
	close(fd);
	return (0);
}
//	PS: might need scene->map[scene->map_row] = NULL; or not
