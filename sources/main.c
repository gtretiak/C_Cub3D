#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;
	if(argc != 2 || !args_checker(argv[1]))
	{
		ft_printf("Invalid argument\n");
		return 1;
	}
	file_reading(argv[1], &map);

	exit(0);
}
