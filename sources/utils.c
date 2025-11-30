#include "../cub3d.h"

void	malloc_error(void)
{
	perror("Malloc failed.\n");
	exit(2);
}

void	init_scene(t_scene *scene)
{
	scene->flag = -6;
	scene->player.on_position = false;
	scene->north.installed = false;
	scene->south.installed = false;
	scene->west.installed = false;
	scene->east.installed = false;
	scene->map_height = 0;
	scene->map = malloc(sizeof(char **));
	if (!scene->map)
		malloc_error();
}

void	free_walls(t_scene *scene)
{
	if (scene->north.installed)
		free(scene->north.path);
	if (scene->south.installed)
		free(scene->south.path);
	if (scene->west.installed)
		free(scene->west.path);
	if (scene->east.installed)
		free(scene->east.path);
}

void	free_scene(t_scene *scene)
{
	free_walls(scene);
	ft_free_array_strn(scene->map, scene->map_height);
}
