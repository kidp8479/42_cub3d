#include "cub3d.h"

static bool	is_header_line(const char *line)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (get_header_entry(line + i) != NULL);
}

static int	count_header_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line_is_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!is_header_line(line))
		{
			free(line);
			break ;
		}
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	check_header_count(const char *path)
{
	int		fd;
	int		count;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	count = count_header_lines(fd);
	close(fd);
	if (count < HEADER_SIZE)
	{
		print_errors(HEADER_MISSING, NULL, NULL);
		return (EXIT_FAILURE);
	}
	else if (count > HEADER_SIZE)
	{
		print_errors(HEADER_TOO_MANY, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
