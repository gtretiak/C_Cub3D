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

	str = get_next_line(fd, 0); //0 means usual flow (comment for debugging)
	printf("Loop\n"); //tmp
	//str = "1S01\n"; //uncomment for debugging
	if (!str)
		return (1);
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
	return (0);
}

int	file_reading(char *file, t_scene *scene)
{
	int		fd;

	init_scene(file, scene);
	fd = open(file, O_RDONLY);
	if (fd < 0) // comment for debugging
	{
		perror("Error opening file");
		exit(1);
	}
	while (!reached_eof(fd, scene))
		;
	printf("finished reading\n"); // tmp
	if (scene->flag != 1 || !scene->player.on_position)
	{
		free_scene(scene);
		close(fd);
		exiter(MAP_NO);
	}
	printf("I'm here\n"); // tmp
	parse_map(fd, scene);
	close(fd);
	printf("success\n");// tmp
	return (0);
}
