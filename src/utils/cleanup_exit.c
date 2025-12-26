#include "cub3d.h"

/**
  * @brief Frees all loaded wall textures
  *
  * Destroys MLX image objects for all 4 wall textures.
  * Checks for NULL before destroying to handle partial initialization.
  *
  * @param game Pointer to game structure
*/
void	cleanup_textures(t_game *game)
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
 * @brief Frees all dynamic allocations inside a t_map structure.
 *
 * This frees the map grid (via free_map_grid), texture paths, and resets
 * floor and ceiling colors to zero. All pointers are set to NULL.
 *
 * @param map Pointer to the t_map structure. Does nothing if NULL.
 *
 * @note Does not free the t_map struct itself.
 * @see free_map_grid()
 */
void	free_t_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	free_map_grid(map);
	i = 0;
	while (i < TEX_SIZE)
	{
		if (map->tex_paths[i])
		{
			free(map->tex_paths[i]);
			map->tex_paths[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (i < RGB_SIZE)
	{
		map->floor_color[i] = 0;
		map->ceiling_color[i] = 0;
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
	free_t_map(&game->map);
	exit(EXIT_SUCCESS);
}
