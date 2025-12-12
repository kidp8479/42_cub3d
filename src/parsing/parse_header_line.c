#include "cub3d.h"

static t_header_type	get_identifier(const char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (ID_NO);
	if (!ft_strncmp(line, "SO", 2))
		return (ID_SO);
	if (!ft_strncmp(line, "WE", 2))
		return (ID_WE);
	if (!ft_strncmp(line, "EA", 2))
		return (ID_EA);
	if (!ft_strncmp(line, "F", 1))
		return (ID_FLOOR);
	if (!ft_strncmp(line, "C", 1))
		return (ID_CEILING);
	return (ID_NONE);
}

static int	parse_header_value(t_map *map, const char *value, t_header_type id)
{
	char	*trimmed_value;
	int		*target_color;

	if (map->id_set[id] == true)
		return (print_errors("duplicate identifier"), EXIT_FAILURE);
	trimmed_value = ft_strtrim(value, " \t\n");
	if (!trimmed_value || trimmed_value[0] == '\0')
		return (free(trimmed_value), EXIT_FAILURE);
	if (id >= ID_NO && id <= ID_EA)
		map->tex_paths[id] = trimmed_value; //pointers will need to be freed eventually
	else
	{
		if (id == ID_FLOOR)
			target_color = map->floor_color;
		else
			target_color = map->ceiling_color;
		if (parse_rgb(trimmed_value, target_color) == EXIT_FAILURE)
		{
			print_errors("rgb");
			return (free(trimmed_value), EXIT_FAILURE);
		}
		free(trimmed_value);
	}
	map->id_set[id] = true;
	return (EXIT_SUCCESS);
}

int	parse_header_line(t_map *map, char *line)
{
	int				i;
	t_header_type	id;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	id = get_identifier(&line[i]);
	if (id == ID_NONE)
		return (EXIT_FAILURE);
	if (id == ID_FLOOR || id == ID_CEILING)
		i += 1;
	else
		i += 2;
	if (!ft_isspace(line[i]))
		return (EXIT_FAILURE);
	if (parse_header_value(map, line + i, id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
