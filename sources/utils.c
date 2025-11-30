#include "../cub3d.h"

void	malloc_error()
{
	perror("Malloc failed.\n");
	exit(2);
}

void	init_scene(t_scene *scene)
{
	scene->flag = -6;
	scene->player.on_position = false;
	scene->floor.rgb[0] = 0;
	scene->floor.rgb[1] = 0;
	scene->floor.rgb[2] = 0;
	scene->ceilling.rgb[0] = 0;
	scene->ceilling.rgb[1] = 0;
	scene->ceilling.rgb[2] = 0;
	scene->map = malloc(sizeof(char**));
	if (!scene->map)
		malloc_error();
}

//static void	free_map(char **map) or free array?

void	free_scene(t_scene *scene) // TODO
{
	//free_walls(scene); NO, SO, EA, WE?
	//free_map(&scene->map); or free_array?
	(void)scene; //tmp
}
