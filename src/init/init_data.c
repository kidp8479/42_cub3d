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
void	init_t_game(t_game *game)
{
	if (!game)
		return ;
	ft_bzero(game, sizeof(t_game));
	game->last_mouse_x = WINDOWS_X / 2;
	game->last_mouse_y = WINDOWS_Y / 2;
}
