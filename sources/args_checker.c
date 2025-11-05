#include "../cub3d.h"
#include <fcntl.h>

static bool is_an_cub_extension(char *map_path)
{
    char *extension;

    extension = ft_strrchr(map_path, '.');
    if(!extension)
        return false;
    if (ft_strncmp(extension, ".cub", 4) != 0)
        return false;
    return true;
}

bool args_checker(char *map_path){
    int fd;

    if(!is_an_cub_extension(map_path))
        return false;
    fd = open(map_path, O_RDONLY);
    if(fd < 0)
        return false;

    return true;
}
