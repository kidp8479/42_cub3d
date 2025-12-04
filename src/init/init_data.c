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
}
