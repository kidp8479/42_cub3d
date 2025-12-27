#include "cub3d.h"

/**
 * @brief Parses and validates a .cub configuration file
 *
 * Orchestrates the full parsing pipeline for a Cub3D map file:
 *   - Verifies header count and identifiers
 *   - Parses texture paths and RGB colors
 *   - Parses the map grid
 *   - Initializes player position and orientation
 *   - Validates map structure and enclosure
 *
 * Frees allocated map resources on failure.
 *
 * @param path Path to the .cub file
 * @param game Pointer to the game structure
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int	parse_and_validate_cub(char *path, t_game *game)
{
	if (check_header_count(path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (parse_header(path, &game->map) != EXIT_SUCCESS)
	{
		free_t_map(&game->map);
		return (EXIT_FAILURE);
	}
	if (parse_map(path, &game->map) != EXIT_SUCCESS)
	{
		free_t_map(&game->map);
		return (EXIT_FAILURE);
	}
	if (init_player(game) != EXIT_SUCCESS)
	{
		free_t_map(&game->map);
		return (EXIT_FAILURE);
	}
	if (check_valid_map(&game->map) != EXIT_SUCCESS)
		return (free_t_map(&game->map), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
