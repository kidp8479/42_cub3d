#include "cub3d.h"

/**
 * @brief Returns the maximum of two integers.
 * @param a First integer.
 * @param b Second integer.
 * @return The larger of a or b.
 */
static int	max_int(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * @brief Reads the .cub file to determine map width and height.
 * @param path Path to the .cub file.
 * @param map Pointer to t_map structure to store dimensions.
 * @return 0 on success, 1 on failure.
 */
static int	get_map_dimensions(const char *path, t_map *map)
{
	int		fd;
	int		len;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
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
 * @brief Loads the map grid from the .cub file into map->grid.
 * @param path Path to the .cub file.
 * @param map Pointer to t_map structure where grid will be stored.
 * @return 0 on success, 1 on failure.
 */
static int	load_map_grid(const char *path, t_map *map)
{
	int		y;
	int		fd;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	map->grid = malloc(sizeof (char *) * map->height);
	if (!map->grid)
		return (close(fd), EXIT_FAILURE);
	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		map->grid[y] = pad_line(line, map->width);
		free(line);
		if (!map->grid[y])
		{
			free_partial_grid(map, y);
			return (close(fd), EXIT_FAILURE);
		}
		y++;
		line = get_next_line(fd);
	}
	return (close(fd), EXIT_SUCCESS);
}

/**
 * @brief Parses a .cub file and fills the t_map structure.
 * 
 * This is the public function to be called from main.c or other modules.
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
		print_errors(LOAD_MAP, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
