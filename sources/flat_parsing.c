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
	static int	is_flat_built[2];
	//floor[0], ceilling[1]
	if (line[0] == 'F')
	{
		if (is_flat_built[0] == 1)
			return (returner(ELEMENT_TYPE));
		is_flat_built[0] = 1;
		status = parse_color(line, &scene->floor);
		if (status)
			return (returner(ELEMENT_UNEXPECTED));
		scene->flag++;
		return (0);
	}
	if (is_flat_built[1] == 1)
		return (returner(ELEMENT_TYPE));
	is_flat_built[1] = 1;
	status = parse_color(line, &scene->ceilling);
	if (status)
		return (returner(ELEMENT_UNEXPECTED));
	scene->flag++;
	return (0);
}
