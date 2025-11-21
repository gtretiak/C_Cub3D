#include "../cub3d.h"

static int	returner(char *str)
{
	printf("%s", str);
	return (1);
}

static int	set_wall(char *line, t_map *map)
{
	/*t_wall	curr;

	curr->path;
	if (open(curr.path, O_RDONLY) < 0)
		return (returner(ELEMENT_PATH));
	if (line[0] == 'N')
		map->north = curr;
	else if (line[0] == 'S')
		map->south = curr;
	else if (line[0] == 'W')
		map->west = curr;
	else
		map->east = curr;
	map->flag++;*/
	(void)line;
	(void)map;
	return (0);
}

static int	set_flat(char *line, t_map *map)
{
	/*t_flat	curr;
	short	i;

	curr.type == line[0];
	i = -1;
	while (line[++i] != '\n' && line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		//rgb, if unexpected - error and return 1
		continue ;
	}
	if (line[0] == 'F')
		map->floor = curr;
	else
		map->ceilling = curr;
	map->flag++;*/
	(void)line;
	(void)map;
	return (0);
}

int	parse_map(char *line, t_map *map)
{
	short	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '\n')
		{
			if (i == 0 && map->flag == 1)
				return (returner(MAP_GAPS));
			return (0);
		}	
		if (ft_isspace(line[i]) && map->flag != 1)
			continue ;
		if (line[0] == 'F' || line[0] == 'C')
			return (set_flat(line, map));
		else if ((line[0] == 'N' && line[1] == 'O')
			|| (line[0] == 'S' && line[1] == 'O')
			|| (line[0] == 'W' && line[1] == 'E')
			|| (line[0] == 'E' && line[1] == 'A'))
			return (set_wall(line, map));
		// test
		//if (...)//error
		//	return (1);
/*
TODO
MAP_WALLS "Error.\nThe map must be closed/surrounded by walls.\n"
MAP_PLAYER "Error.\nThere can't be more than one player.\n"
MAP_UNEXPECTED "Error.\nUnexpected char found in the map.\n"
MAP_LAST "Error.\nThe map must be the last element of *.cub.\n"
MAP_NO "Error.\nThere is no map in your cub file.\n"
ELEMENT_TYPE "Error.\nElement type is missing (invalid).\n"
ELEMENT_UNEXPECTED "Error.\nUnexpected char found in an element.\n"
*/
	}
	(void)line; // tmp
	(void)map; //tmp
	return (0);
}

void	file_reading(char *file, t_map *map)
{
	int	fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(1);
	}
	init_map(map);
	while (1)
	{
		str = get_next_line(fd, 0); //recall workflow TODO
		if (!str)
			break ;
		if (parse_map(str, map)) // might include just \n (empty)
		{
			free(str);
			free_map(map);
			exit(1);
		}
		free(str);
	}
	close(fd);
}
