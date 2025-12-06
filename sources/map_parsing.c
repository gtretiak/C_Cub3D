#include "../cub3d.h"

static int	handle_player(t_scene *scene, char c, int i)
{
	if (scene->player.on_position)
		return (returner(MAP_PLAYER));
	scene->player.direction = c;
	scene->player.point.x = i;
	scene->player.point.y = scene->map_height;
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

	i = 0;
	scene->flag = 1;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (char_processing(line[i], scene, i))
			return (1);
		i++;
	}
	scene->map[scene->map_height] = ft_strdup(line);
	if (!scene->map[scene->map_height])
		malloc_error();
	*ft_strchr(scene->map[scene->map_height], '\0') = line[i];
	//if line[i] = '\n', then my scene->map line isn't terminated.TODO
	return (0);
}

void	parse_map(char **map)// TODO
{
	// if (ft_isspace(current char))
	// 	current char == '1'; or something else
	//MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
	(void)map;
}
