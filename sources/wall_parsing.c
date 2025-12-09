/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:06:55 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 18:11:49 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_wall(char *line, t_wall *wall, t_scene *scene)
{
	short	i;
	size_t	len;
	char	*last_char_ptr;

	i = 2;
	while (ft_isspace(line[i]))
		i++;
	len = ft_strlen(line);
	wall->path = ft_substr(line, i, len - i);
	if (!wall->path)
		malloc_error(scene);
	last_char_ptr = ft_strchr(wall->path, '\n');
	if (last_char_ptr)
		*last_char_ptr = '\0';	
	if (open(wall->path, O_RDONLY) < 0)
		return (returner(ELEMENT_PATH));
	return (0);
}
//PS: do I need this? *ft_strchr(wall->path, '\0') = line[len];

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
