#include "cub3d.h"

/**
 * @brief Main game loop - called every frame by MLX
 *
 * Executes the main rendering pipeline:
 * 1. Processes input - checks which keys are pressed and executes actions
 * 2. Clears the window - prevents trailing artifacts from previous frame
 * 3. Renders the scene - casts WINDOWS_X rays (one per screen column)
 * 4. Displays the result - pushes image buffer to window
 *
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	game_loop(void *param)
{
	t_game			*game;
	t_key_binding	*bindings;
	int				i;

	game = (t_game *)param;
	bindings = get_key_bindings(game);
	i = 0;
	while (bindings[i].action)
	{
		if (*bindings[i].flag_ptr)
			bindings[i].action(game);
		i++;
	}
	// clear the window before rendering new frame
	mlx_clear_window(game->mlx, game->win);
	// render full frame (WINDOWS_X)
	render_frame(game);
	// display the rendered frame
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (EXIT_SUCCESS);
}
