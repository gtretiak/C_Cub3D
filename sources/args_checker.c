/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:51:17 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 16:51:19 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
