/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 17:27:17 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/09 10:46:21 by rimagalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_scene	scene;

	args_checker(argc, argv);
	file_reading(argv[1], &scene);
	ft_render(&scene);
	exit(0);
}
