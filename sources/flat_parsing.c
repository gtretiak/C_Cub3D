/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 16:59:28 by gtretiak          #+#    #+#             */
/*   Updated: 2025/12/06 16:59:49 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_component(char *line, short *i, int *value)
{
	short	counter;

	counter = 0;
	*value = 0;
	while (ft_isdigit(line[*i]))
	{
		if (counter >= 3)
			return (1);
		*value *= 10;
		*value += line[*i] - '0';
		(*i)++;
		counter++;
	}
	if (*value > 255 || counter == 0)
		return (1);
	return (0);
}

static int	parse_color(char *line, t_flat *flat) //returns 1 - bug!
{
	short	i;
	short	j;

	i = 1;
	j = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		while (ft_isspace(line[i]))
			i++;
		if (parse_component(line, &i, &flat->rgb[j]))
			return (1);
		if (j < 2)
		{
			if (line[i] != ',')
				return (1);
			i++;
		}
		else if (j == 2)
		{
			if (line[i] != '\n' && line[i] != '\0')
				return (1);
		}
		while (ft_isspace(line[i]))
			i++;
		j++;
	}
	flat->color = (flat->rgb[0] << 16) | (flat->rgb[1] << 8) | flat->rgb[2];
	return (0);
}

int	set_flat(char *line, t_scene *scene)
{
	int			status;

	if (line[0] == 'F')
	{
		if (scene->floor.installed == true)
			return (returner(ELEMENT_TYPE));
		scene->floor.installed = true;
		status = parse_color(line, &scene->floor);
		if (status)
			return (returner(ELEMENT_UNEXPECTED));
		scene->flag++;
		return (0);
	}
	if (scene->ceilling.installed == true)
		return (returner(ELEMENT_TYPE));
	scene->ceilling.installed = true;
	status = parse_color(line, &scene->ceilling);
	if (status)
		return (returner(ELEMENT_UNEXPECTED));
	scene->flag++;
	return (0);
}
