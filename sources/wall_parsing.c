/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:06:55 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/16 12:00:29 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	xpm_extension(char *texture_path)
{
	char	*extension;

	extension = ft_strrchr(texture_path, '.');
	if (!extension || ft_strncmp(extension, ".xpm", 4))
		return (1);
	return (0);
}

static int	parse_wall(char *line, t_wall *wall, t_scene *scene)
{
	short	i;
	size_t	len;
	char	*last_char_ptr;

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	len = ft_strlen(line);
	wall->path = ft_substr(line, i, len - i - 1);
	if (!wall->path)
		malloc_error(scene);
	last_char_ptr = ft_strchr(wall->path, '\n');
	if (last_char_ptr)
		*last_char_ptr = '\0';
	if (xpm_extension(wall->path) || open(wall->path, O_RDONLY) < 0)
	{
		free(wall->path);
		return (returner(ELEMENT_PATH));
	}
	return (0);
}

static int	set_wall(char *line, t_wall *wall, t_scene *scene)
{
	int	status;

	if (wall->installed)
		return (returner(ELEMENT_TYPE));
	status = parse_wall(line, wall, scene);
	if (status)
		return (1);
	wall->installed = true;
	scene->flag++;
	return (0);
}

int	define_wall(char *line, t_scene *scene)
{
	if (line[0] == 'N' && line[1] && line[1] == 'O')
		return (set_wall(line, &scene->north, scene));
	else if (line[0] == 'S' && line[1] && line[1] == 'O')
		return (set_wall(line, &scene->south, scene));
	else if (line[0] == 'E' && line[1] && line[1] == 'A')
		return (set_wall(line, &scene->east, scene));
	else if (line[0] == 'W' && line[1] && line[1] == 'E')
		return (set_wall(line, &scene->west, scene));
	return (returner(ELEMENT_UNEXPECTED));
}
