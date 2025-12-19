#include "cub3d.h"

/**
  * @brief Frees all loaded wall textures
  *
  * Destroys MLX image objects for all 4 wall textures.
  * Checks for NULL before destroying to handle partial initialization.
  *
  * @param game Pointer to game structure
*/
static void	cleanup_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_SIZE)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}

/**
  * @brief Cleans up all game resources and exits program
  *
  * Destroys MLX resources (image, window, display) and frees game data.
  * Called when user presses ESC or clicks window close button.
  * Order of operations matters
  *
  * @param game Pointer to game structure
*/
void	cleanup_exit(t_game *game)
{
	if (!game)
		exit(EXIT_FAILURE);
	if (game->mlx)
		cleanup_textures(game);
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
