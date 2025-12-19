#include "cub3d.h"

/**
 * @brief Compute map width and height from a .cub file.
 *
 * Reads the file line by line and counts only lines belonging to the map,
 * starting at map->map_start_line. The map width is set to the length of
 * the longest map line (excluding the trailing newline). The map height
 * is the number of map lines.
 *
 * @param path Path to the .cub file.
 * @param map  Pointer to the map structure to fill dimensions.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on file open error.
 */
static int	get_map_dimensions(const char *path, t_map *map)
{
	int		fd;
	int		len;
	int		i;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	gnl_clear_fd(fd);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i >= map->map_start_line)
		{
			len = ft_strlen(line);
			if (line[len - 1] == '\n')
				len--;
			map->width = max_int(map->width, len);
			map->height++;
		}
		next_line(&line, fd, &i);
	}
	gnl_clear_fd(fd);
	return (close(fd), EXIT_SUCCESS);
}

/**
 * @brief Pads a line with spaces to match the map width.
 * @param row The input line from the .cub file.
 * @param width The desired width of the padded line.
 * @return A newly allocated string with padding, or NULL on malloc failure.
 */
static char	*pad_line(const char *row, int width)
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

/**
 * @brief Store a single line of the map into the map grid.
 *
 * Pads the line to the map width and stores it in map->grid. Skips lines
 * before map_start_line. On allocation failure, frees allocated memory
 * for the partial grid and returns EXIT_FAILURE.
 *
 * @param map Pointer to the map structure.
 * @param i Current line index in the .cub file.
 * @param y Pointer to the current row index in map->grid.
 * @param line Line content read from the .cub file.
 * @return EXIT_SUCCESS if line is stored or skipped, EXIT_FAILURE if
 *         memory allocation fails.
 */
static int	store_map_line(t_map *map, int i, int *y, char *line)
{
	if (i < map->map_start_line)
		return (EXIT_SUCCESS);
	map->grid[*y] = pad_line(line, map->width);
	if (!map->grid[*y])
	{
		free(line);
		free_partial_grid(map, *y);
		return (EXIT_FAILURE);
	}
	(*y)++;
	return (EXIT_SUCCESS);
}

/**
 * @brief Loads the map grid from a .cub file into map->grid.
 *
 * Reads each line from the file, pads it to the map width, and stores it in
 * map->grid. Skips header lines before map_start_line. Frees memory and closes
 * the file on error.
 *
 * @param path Path to the .cub file.
 * @param map Pointer to the t_map structure to populate.
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on malloc or I/O failure.
 */
static int	load_map_grid(const char *path, t_map *map)
{
	int		y;
	int		fd;
	int		i;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	gnl_clear_fd(fd);
	map->grid = malloc(sizeof (char *) * map->height);
	if (!map->grid)
		return (close(fd), EXIT_FAILURE);
	y = 0;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (store_map_line(map, i, &y, line) == EXIT_FAILURE)
			return (free(line), close(fd), EXIT_FAILURE);
		next_line(&line, fd, &i);
	}
	gnl_clear_fd(fd);
	close(fd);
	return (EXIT_SUCCESS);
}

/**
 * @brief Parses a .cub file and fills the t_map structure.
 * 
 * It reads the .cub file, calculates dimensions, and loads the grid.
 *
 * @param path Path to the .cub file.
 * @param map Pointer to t_map structure to fill.
 * @return 0 on success, 1 on failure.
 *
 * @note **Currently, no validation of the map contents is performed.**
 *       Only the map dimensions and grid are loaded and padded.
 */
int	parse_map(const char *path, t_map *map)
{
	if (get_map_dimensions(path, map))
	{
		print_errors(MAP_DIMENSIONS, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (load_map_grid(path, map))
	{
		print_errors(MAP_LOAD, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
