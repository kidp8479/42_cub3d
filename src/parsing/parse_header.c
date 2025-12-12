#include "cub3d.h"

static void	next_line(char **line, int fd, int *i)
{
	free(*line);
	*line = get_next_line(fd);
	(*i)++;
}

static bool	skip_empty_lines(char **line, int fd, int *i)
{
	while (*line && line_is_empty(*line))
	{
		free(*line);
		*line = get_next_line(fd);
		(*i)++;
	}
	if (*line == NULL)
		return (false);
	return (true);
}

static bool	line_is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (false);
		i++;
	}
	return (true);
}

int	parse_header(const char *path, t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	line = get_next_line(line);
	i = 0;
	while (line)
	{
		if (!skip_empty_lines(&line, fd, &i))
			return (close(fd), EXIT_FAILURE);
		if (parse_header_line(map, line) == EXIT_FAILURE)
			return (free(line), close(fd), EXIT_FAILURE);
		if (all_headers_set(map))
		{
			map->map_start_line = i + 1;
			free(line);
			break ;
		}
		next_line(&line, fd, &i);
	}
	return (close(fd), EXIT_SUCCESS);
}
