/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:56:07 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 16:56:38 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_it_map_line(char *line)
{
	short	i;

	i = -1;
	while (line[++i] && line[i] != '\n')
	{
		if (ft_isspace(line[i]))
			continue ;
		if (line[i] == '1')
			return (1);
	}
	return (0);
}

static void	init_map(int fd, t_scene *scene)
{
	short	i;
	char	*line;

	while (1)
	{
		line = get_next_line(fd, 0);
		if (!line)
			break ;
		if (is_it_map_line(line))
			scene->map_size.y++;
		free(line);
	}
	close(fd);
	if (scene->map_size.y == 0)
		exiter(MAP_NO);
	else if (scene->map_size.y < 3)
		exiter(MAP_INV);
	scene->map = malloc(sizeof(char *) * (scene->map_size.y + 1));
	if (!scene->map)
		malloc_error();
	i = 0;
	while (i < scene->map_size.y + 1)
		scene->map[i++] = NULL;
}

void	init_scene(char *file, t_scene *scene)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	scene->flag = -6;
	scene->player.on_position = false;
	scene->ceilling.installed = false;
	scene->floor.installed = false;
	scene->north.installed = false;
	scene->south.installed = false;
	scene->west.installed = false;
	scene->east.installed = false;
	scene->map_size.x = 0;
	scene->map_size.y = 0;
	scene->map_row = 0;
	init_map(fd, scene);
}
