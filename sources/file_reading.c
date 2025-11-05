#include "../cub3d.h"

int	parse_map(char *line, t_map *map)
{
	/*short	i;

	i = 0;
	while (line[i] != '\n' && line[i] != EOF)
	{
		if (...)//error
			return (1);
	}
	*/
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
		str = get_next_line(fd, 2);
		if (!str)
			break ;
		if (parse_map(str, map))
			break ;
		free(str);
	}
	close(fd);
}
