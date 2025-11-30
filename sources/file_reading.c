#include "../cub3d.h"

static int	returner(char *str)
{
	printf("%s", str);
	return (1);
}

static int	parse_wall(char *line, t_wall *wall)
{
	short	i;
	short	j;
	size_t	len;

	i = 2;
	j = 0;
	while (ft_isspace(line[i]))
		i++;
	len = ft_strlen(line);
	wall->path = ft_substr(line, i, len - i);
	if (!wall->path)
		malloc_error();
	*ft_strchr(wall->path, '\0') = line[len];
	if (open(wall->path, O_RDONLY) < 0)
	{
		printf("no texture\n"); // tmp
		return (returner(ELEMENT_PATH));
	}
	return (0);
}

static int	set_wall(char *line, t_wall *wall, t_scene *scene)
{
	int	status;

	if (wall->installed)
		return (returner(ELEMENT_TYPE));
	status = parse_wall(line, wall);
	wall->installed = true;
	if (status)
		return (1);
	scene->flag++;
	return (0);
}

static int	define_wall(char *line, t_scene *scene)
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

static int	parse_component(char *line, short *i, int *value)
{
	short	counter;

	counter = 0;
	*value = 0;
	while (ft_isdigit(line[*i]))
	{
		if (counter >= 3)
			return (1);
		*value *= 10;
		*value += line[*i] - '0';
		(*i)++;
		counter++;
	}
	if (*value > 255 || counter == 0)
		return (1);
	return (0);
}

static int	parse_color(char *line, t_flat *flat)
{
	short	i;
	short	j;

	i = 1;
	j = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		if (parse_component(line, &i, &flat->rgb[j]))
			return (1);
		if (((line[i] == '\n' || line[i] == '\0') && j != 2)
			|| line[i++] != ',')
			return (1);
		while (ft_isspace(line[i]))
			i++;
		j++;
	}
	flat->color = (flat->rgb[0] << 16) | (flat->rgb[1] << 8) | flat->rgb[2];
	return (0);
}

static int	set_flat(char *line, t_scene *scene)
{
	int			status;
	static int	is_flat_built[2];
	//floor[0], ceilling[1]
	if (line[0] == 'F')
	{
		if (is_flat_built[0] == 1)
			return (returner(ELEMENT_TYPE));
		is_flat_built[0] = 1;
		status = parse_color(line, &scene->floor);
		if (status)
			return (returner(ELEMENT_UNEXPECTED));
		scene->flag++;
		return (0);
	}
	if (is_flat_built[1] == 1)
		return (returner(ELEMENT_TYPE));
	is_flat_built[1] = 1;
	status = parse_color(line, &scene->ceilling);
	if (status)
		return (returner(ELEMENT_UNEXPECTED));
	scene->flag++;
	return (0);
}

int	handle_player(t_scene *scene, char c, int i)
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
	short	j;

	i = -1;
	j = 0;
	scene->flag = 1;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (char_processing(line[i], scene, i))
			return (1);
		i++;
	}
	scene->map[scene->map_height] = ft_strdup(line);
	if (!scene->map[scene->map_height])
		malloc_error();
	*ft_strchr(scene->map[scene->map_height], '\0') = line[i];
	return (0);
}

int	parse_scene(char *line, t_scene *scene)// TODO shorter (split)
{
	short	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '1' || line[0] == '0')
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
		if (line[0] == 'F' || line[0] == 'C')
			return (set_flat(line, scene));
		if ((line[0] == 'N') || (line[0] == 'S')
			|| (line[0] == 'W') || (line[0] == 'E'))
			return (define_wall(line, scene));
		if (scene->flag == 1)
			return (returner(MAP_UNEXPECTED));
		return (returner(ELEMENT_UNEXPECTED));
	}
	return (0);
}

void	parse_map(char **map)// TODO
{
	// if (ft_isspace(current char))
	// 	current char == '1'; or something else
	//MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
	(void)map;
}

int	file_reading(char *file, t_scene *scene)//TODO shorter (split)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd < 0) // comment for debugging
	{
		perror("Error opening file");
		exit(1);
	}
	init_scene(scene);
	while (1)
	{
		str = get_next_line(fd, 0); //0 means usual flow (comment for debugging)
		printf("Loop\n"); //tmp
		//str = "1S01\n"; //uncomment for debugging
		if (!str)
			break ;
		if (parse_scene(str, scene)) // might include just \n (empty)
		{
			free(str);
			str = get_next_line(fd, 2); //2 means freeing static tmp
			free(str);
			free_scene(scene);
			close(fd);
			exit(1);
		}
		free(str); //comment for debugging
	}
	printf("finished reading\n"); // tmp
	if (scene->flag != 1)
	{
		free_scene(scene);
		close(fd);
		exiter(MAP_NO);
	}
	printf("I'm here\n"); // tmp
	parse_map(scene->map);
	close(fd);
	printf("success\n");// tmp
	return (0);
}
