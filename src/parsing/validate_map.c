/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:03:27 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 14:03:29 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Ensure all map characters are valid ('0', '1', or space).
 *
 * Iterates the map grid. Prints an error and returns EXIT_FAILURE if any
 * invalid character is found.
 *
 * @param map Pointer to the t_map structure.
 * @return EXIT_SUCCESS if all characters are valid, else EXIT_FAILURE.
 */
static int	check_allowed_chars(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c != '1' && c != '0' && c != ' ')
			{
				print_errors(MAP_CHAR, NULL, NULL);
				return (EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Check if coordinates are within the map boundaries.
 *
 * @param map Pointer to the map structure.
 * @param y   Row index to check.
 * @param x   Column index to check.
 * @return true if (y, x) is inside the map, false otherwise.
 */
static bool	in_bounds(t_map *map, int y, int x)
{
	if (y >= 0 && y < map->height && x >= 0 && x < map->width)
		return (true);
	return (false);
}

/**
 * @brief Check that a '0' cell is only adjacent to '0' or '1'.
 *
 * ny and nx stand for the neighboring cell coordinates. The dir_y and dir_x
 * tables define the relative positions (up, down, left, right) to check.
 *
 * @param map Pointer to the map structure.
 * @param y   Row index of the '0' cell.
 * @param x   Column index of the '0' cell.
 * @return EXIT_SUCCESS if all neighbors are valid, EXIT_FAILURE otherwise.
 */
static int	check_zero_adjacent(t_map *map, int y, int x)
{
	const int	dir_y[ADJACENT_DIR_COUNT] = {1, -1, 0, 0};
	const int	dir_x[ADJACENT_DIR_COUNT] = {0, 0, 1, -1};
	int			i;
	int			ny;
	int			nx;

	i = 0;
	while (i < ADJACENT_DIR_COUNT)
	{
		ny = y + dir_y[i];
		nx = x + dir_x[i];
		if (!in_bounds(map, ny, nx))
		{
			print_errors(MAP_ZERO_BORDER, NULL, NULL);
			return (EXIT_FAILURE);
		}
		if (map->grid[ny][nx] != '0' && map->grid[ny][nx] != '1')
		{
			print_errors(MAP_ZERO_INVALID, NULL, NULL);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Check that a space cell is not adjacent to a '0' cell.
 *
 * ny and nx are the neighboring cell coordinates. dir_y and dir_x define
 * relative positions (up, down, left, right) to inspect.
 *
 * @param map Pointer to the map structure.
 * @param y   Row index of the space cell.
 * @param x   Column index of the space cell.
 * @return EXIT_SUCCESS if all neighbors are valid, EXIT_FAILURE otherwise.
 */
static int	check_space_adjacent(t_map *map, int y, int x)
{
	const int	dir_y[ADJACENT_DIR_COUNT] = {1, -1, 0, 0};
	const int	dir_x[ADJACENT_DIR_COUNT] = {0, 0, 1, -1};
	int			i;
	int			ny;
	int			nx;

	i = 0;
	while (i < ADJACENT_DIR_COUNT)
	{
		ny = y + dir_y[i];
		nx = x + dir_x[i];
		if (in_bounds(map, ny, nx))
		{
			if (map->grid[ny][nx] == '0')
			{
				print_errors(MAP_SPACE, NULL, NULL);
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Validate the map by checking all characters and adjacency rules.
 *
 * Iterates through the map grid and checks each cell:
 *  - '0' cells must be surrounded by '0' or '1'.
 *  - ' ' cells must not touch any '0'.
 *
 * @param map Pointer to the map structure.
 * @return EXIT_SUCCESS if all checks pass, EXIT_FAILURE otherwise.
 */
int	check_valid_map(t_map *map)
{
	int	y;
	int	x;

	if (map->width > MAX_MAP_W || map->height > MAX_MAP_H)
		return (print_errors(MAP_TOO_LARGE, NULL, NULL), EXIT_FAILURE);
	if (check_allowed_chars(map) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0'
				&& check_zero_adjacent(map, y, x) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else if (map->grid[y][x] == ' '
				&& check_space_adjacent(map, y, x) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}
