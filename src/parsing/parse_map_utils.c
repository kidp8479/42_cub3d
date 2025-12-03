#include "cub3d.h"

/**
 * @brief Opens a .cub file for reading.
 * 
 * Wrapper around open() that prints an error message if the file
 * cannot be opened.
 *
 * @param path Path to the .cub file.
 * @return File descriptor on success, -1 on failure.
 */
int	open_cub_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("cub3d");
	return (fd);
}

/**
 * @brief Prints the map grid to stdout for debugging.
 * 
 * Spaces in the map are displayed as '.' to make them visible.
 * This includes both padding added by the parser and any spaces
 * that were already present in the map. It does not distinguish
 * between the two.
 * 
 * Does not modify the map.
 *
 * @param map Pointer to the t_map structure containing the grid.
 */
void	print_map_grid(t_map *map)
{
	int		y;
	int		x;
	char	c;

	if (!map || !map->grid)
		return ;
	printf("Map dimensions: %d x %d\n", map->width, map->height);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c == ' ')
				ft_putchar_fd('.', 0);
			else
				ft_putchar_fd(c, 0);
			x++;
		}
		ft_putchar_fd('\n', 0);
		y++;
	}
}

/**
 * @brief Frees all memory allocated for the map grid.
 * 
 * Frees each row of map->grid, then the grid itself.
 * Resets map width and height to 0. Safe to call on NULL pointers.
 *
 * @param map Pointer to the t_map structure to free.
 */
void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	map->width = 0;
	map->height = 0;
}
