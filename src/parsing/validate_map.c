#include "cub3d.h"

/**
 * @brief Check if a character is valid in the map.
 *
 * Valid characters are '0', '1', and space (' ').
 *
 * @param c The character to check.
 * @return true if valid, false otherwise.
 */
static bool	is_valid_map_char(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return (true);
	return (false);
}

/**
 * @brief Ensure all characters in the map are valid.
 *
 * Iterates through the map grid and checks each character using
 * is_valid_map_char(). Prints an error if an invalid character is found.
 *
 * @param map Pointer to the map structure.
 * @return EXIT_SUCCESS if all chars are valid, otherwise EXIT_FAILURE.
 */
static int	check_allowed_chars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!is_valid_map_char(map->grid[y][x]))
			{
				print_errors("Invalid map chars", NULL, NULL);
				return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Perform a flood fill to check if the map is enclosed.
 *
 * Recursively marks all reachable '0' tiles starting from (y, x) in the
 * provided grid. Stops at walls ('1') or already visited tiles ('v').
 * If a space (' ') or out-of-bounds is reached, it returns failure.
 *
 * @param grid  The temporary map grid to operate on.
 * @param map   Pointer to the map structure.
 * @param y     Starting row for flood fill.
 * @param x     Starting column for flood fill.
 * @return EXIT_SUCCESS if the filled area is enclosed, otherwise EXIT_FAILURE.
 */
static int	flood_fill(char **grid, t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
	{
		print_errors("map not fully enclosed", NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (grid[y][x] == ' ')
	{
		print_errors("map not fully enclosed", NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (grid[y][x] == '1' || grid[y][x] == 'v')
		return (EXIT_SUCCESS);
	grid[y][x] = 'v';
	if (flood_fill(grid, map, y + 1, x) == EXIT_FAILURE
		|| flood_fill(grid, map, y - 1, x) == EXIT_FAILURE
		|| flood_fill(grid, map, y, x + 1) == EXIT_FAILURE
		|| flood_fill(grid, map, y, x - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/**
 * @brief Create a deep copy of the map grid.
 *
 * Allocates a new 2D array and duplicates each row of the original map.
 * If any allocation fails, all previously allocated rows are freed
 * and NULL is returned.
 *
 * @param map Pointer to the map structure containing the source grid.
 * @return A newly allocated copy of the map grid, or NULL on failure.
 */
static char	**copy_map(t_map *map)
{
	int		row;
	char	**copy;

	copy = malloc(sizeof(char *) * map->height);
	if (!copy)
		return (NULL);
	row = 0;
	while (row < map->height)
	{
		copy[row] = ft_strdup(map->grid[row]);
		if (!copy[row])
		{
			while (--row >= 0)
				free(copy[row]);
			free(copy);
			return (NULL);
		}
		row++;
	}
	return (copy);
}

/**
 * @brief Validate the map by checking chars and running flood fill.
 *
 * Duplicates the map, performs flood fill from the player's start position,
 * and ensures the map is enclosed. The original map is never modified.
 * The temporary copy is always freed before returning.
 *
 * @param map    Pointer to the map structure.
 * @param player Pointer to the player structure.
 * @return EXIT_SUCCESS if valid, otherwise EXIT_FAILURE.
 */
int	check_valid_map(t_map *map, t_player *player)
{
	char	**tmp;

	if (check_allowed_chars(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	tmp = copy_map(map);
	if (!tmp)
	{
		printf("debug: malloc failure");
		return (EXIT_FAILURE);
	}
	if (flood_fill(tmp, map, player->pos_y, player->pos_x) == EXIT_FAILURE)
	{
		free_map_copy(tmp, map->height);
		return (EXIT_FAILURE);
	}
	free_map_copy(tmp, map->height);
	return (EXIT_SUCCESS);
}
