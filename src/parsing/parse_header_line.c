#include "cub3d.h"

static bool	validate_texture_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_errors(TEXTURE_INVALID, NULL, NULL);
		return (false);
	}
	close(fd);
	return (true);
}

static int	set_texture_path(t_map *map, t_header_type id, const char *path)
{
	char	*trimmed_value;

	trimmed_value = ft_strtrim(path, " \t\n");
	if (!trimmed_value)
	{
		print_errors(TEXTURE_TRIM_FAIL, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (trimmed_value[0] == '\0')
	{
		print_errors(TEXTURE_EMPTY, NULL, NULL);
		free(trimmed_value);
		return (EXIT_FAILURE);
	}
	if (!validate_texture_file(trimmed_value))
	{
		free(trimmed_value);
		return (EXIT_FAILURE);
	}
	map->tex_paths[id] = trimmed_value;
	return (EXIT_SUCCESS);
}

static int	set_rgb_color(t_map *map, t_header_type id, const char *value)
{
	int	*rgb_values;

	if (id == ID_FLOOR)
		rgb_values = map->floor_color;//points to first value of array
	else
		rgb_values = map->ceiling_color;
	if (parse_rgb(value, rgb_values) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_header_value(t_map *map, const char *value, t_header_type id)
{
	if (map->id_set[id] == true)
	{
		print_errors(HEADER_DUPLICATE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (id >= ID_NO && id <= ID_EA)
	{
		if (set_texture_path(map, id, value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
	{
		if (set_rgb_color(map, id, value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	map->id_set[id] = true;
	return (EXIT_SUCCESS);
}

int	parse_header_line(t_map *map, char *line)
{
	int						i;
	const t_header_entry	*entry;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	entry = get_header_entry(line + i);
	if (!entry)
		return (EXIT_FAILURE);
	i += entry->len;
	if (!ft_isspace(line[i]))
		return (EXIT_FAILURE);
	if (parse_header_value(map, line + i, entry->id) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
