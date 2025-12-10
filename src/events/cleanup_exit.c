#include "cub3d.h"

/**
  * @brief Cleans up all game resources and exits program
  *
  * Destroys MLX resources (image, window, display) and frees game data.
  * Called when user presses ESC or clicks window close button.
  *
  * @param game Pointer to game structure
*/
void	cleanup_exit(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map.grid)
		free_map(&game->map);
	exit(EXIT_SUCCESS);
}
