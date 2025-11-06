#include "../cub3d.h"

int	parse_map(char *line, t_map *map)
{
	short	i;

	i = -1;
	while (line[++i] != '\0' && line[i] != '\n')
	{
		if (line[0] == '\n')
		{
			if (map->flag == true)
			{
				printf(MAP_GAPS);
				return (1);
			}
			continue ;
		}	
		if (ft_isspace(line[i]))
			continue ;
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
ELEMENT_PATH "Error.\nTexture path/file is invalid/inaccessible.\n"
*/
		i++;
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
	while (1)
	{
		str = get_next_line(fd, 0); //recall workflow TODO
		if (!str)
			break ;
		if (parse_map(str, map)) // might include just \n (empty)
		{
			free(str);
			exit(1);
		}
		free(str);
	}
	close(fd);
}
