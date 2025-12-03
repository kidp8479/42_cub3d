#include "cub3d.h"

static int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	get_map_dimensions(const char *path, t_map *map)
{
	int		fd;
	int		len;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (1);
	map->width = 0; //delete once init_data is implemented
	map->height = 0; //delete once init_data is implemented
	line = get_next_line(fd);
	while (line)
	{
		len = 0;
		while (line[len] && line[len] != '\n')
			len++;
		map->width = max_int(map->width, len);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

char	*pad_line(const char *row, int width)
{
	char	*padded_line;
	int		i;

	padded_line = malloc(width + 1);
	if (!padded_line)
		return (NULL);
	i = 0;
	while (row[i] && row[i] != '\n')
	{
		padded_line[i] = row[i];
		i++;
	}
	while (i < width)
		padded_line[i++] = ' ';
	padded_line[i] = '\0';
	return (padded_line);
}

int	load_map_grid(const char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		y; // row

	fd = open_cub_file(path);
	if (fd < 0)
		return (1);
	map->grid = malloc(sizeof (char *) * map->height);
	if (!map->grid)
		return (close(fd), 1);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->grid[y] = pad_line(line, map->width);
		free(line);
		if (!map->grid[y])
			return (close(fd), 1);
		y++;
		line = get_next_line(fd);
	}
	close (fd)
	return (0);
}

int	parse_map(const char *path, t_map *map)
{
	if (get_map_dimensions(path, map))
	{
		printf("Error: invalid map dimensions\n");
		return (1);
	}
	if (load_map_grid(path, map))
	{
		printf("Error: failed loading map grid\n");
		return (1);
	}
	return (0);
}
