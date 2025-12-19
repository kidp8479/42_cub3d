#include "cub3d.h"

/**
 * @brief Initializes the game data structure to a clean state.
 *
 * This function zeroes out the entire t_game structure, including
 * all nested structs such as t_map and t_player.
 *
 * @param game Pointer to the t_game structure to initialize.
 *
 * @note Safe to call on a partially initialized t_game structure.
 */
void	init_data(t_game *game)
{
	if (!game)
		return ;
	// Zero out entire struct including any nested structs and its fields
	ft_bzero(game, sizeof(t_game));
	// Initialize mouse position to center of window
	game->last_mouse_x = WINDOWS_X / 2;
	game->last_mouse_y = WINDOWS_Y / 2;
}

int	load_and_validate_map(char *path, t_game *game)
{
	if (validate_argument(path) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_data(game);
	if (parse_map(path, &game->map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_player(game) != EXIT_SUCCESS)
	{
		free_map(&game->map);
		return (EXIT_FAILURE);
	}
	if (check_valid_map(&game->map) != EXIT_SUCCESS)
	{
		free_map(&game->map);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
