#include "cub3d.h"

/**
 * @brief Registers all event hooks for the game window.
 *
 * Sets up keyboard press/release events, window close event,
 * and mouse movement handling. These functions allow the game
 * to react to player inputs during runtime.
 * Centers the cursor at startup for FPS-style mouse look.
 *
 * @param game Pointer to the game structure containing MLX window.
 */
void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_hook(game->win, 3, 1L << 1, handle_keyrelease, game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse_move, game);
	mlx_mouse_move(game->mlx, game->win, WINDOWS_X / 2, WINDOWS_Y / 2);
}
