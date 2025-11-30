#include "../cub3d.h"

void	exiter(char *str)
{
	if (str)
		ft_printf("%s", str);
	else
		perror("Error:");
	exit(1);
}

static void	cub_extension(char *map_path)
{
	char	*extension;
	
	extension = ft_strrchr(map_path, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4))
		exiter(ARG_INV);
	return ;
}

void	args_checker(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		exiter(ARG_NUM);
	cub_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exiter(NULL);
	return ;
}
