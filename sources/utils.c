#include "../cub3d.h"

void	malloc_error()
{
	perror("Malloc failed.\n");
	exit(2);
}

void	init_map(t_map *map)
{
	map->flag = false;
	map->map = malloc(sizeof(char**));
	if (!map->map)
		malloc_error();
}

void	free_map(t_map *map)
{
	(void)map; //tmp
}
