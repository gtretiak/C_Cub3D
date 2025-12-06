#include "../cub3d.h"

void	malloc_error(void)
{
	perror("Malloc failed.\n");
	exit(2);
}

int	returner(char *str)
{
	printf("%s", str);
	return (1);
}

void	exiter(char *str)
{
	if (str)
		ft_printf("%s", str);
	else
		perror("Error:");
	exit(1);
}

static void	free_walls(t_scene *scene)
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
