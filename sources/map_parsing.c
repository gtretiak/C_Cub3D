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

	i = 0;
	scene->flag = 1;
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
		malloc_error();
	//*ft_strchr(scene->map[scene->map_row], '\0') = line[i];//Do I need it? TODO
	//if line[i] = '\n', then my scene->map line isn't terminated?TODO
	scene->map_row++;
	return (0);
}

static int	flood_fill(t_scene *scene, int row, int col)
{
	if (row < 0 || row >= scene->map_size.y
		|| col < 0 || col >= (int)ft_strlen(scene->map[row]))
		return (0);
	if (scene->map[row][col] == '1' || scene->map[row][col] == 'f'
		|| scene->map[row][col] == scene->player.direction)
		return (0);
	if (scene->map[row][col] == '0')
		scene->map[row][col] = 'f';
	if (scene->map[row][col] != '0' && scene->map[row][col] != 'f'
		&& scene->map[row][col] != '1')
		return (1);
	flood_fill(scene, row - 1, col);
	flood_fill(scene, row + 1, col);
	flood_fill(scene, row, col + 1);
	flood_fill(scene, row, col - 1);
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
