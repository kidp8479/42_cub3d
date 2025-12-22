#include "cub3d.h"

/**
 * @brief Entry point of the Cub3D program
 *
 * This function orchestrates the entire program execution:
 *   1. Validates command-line arguments (expects exactly one .cub file)
 *   2. Loads, parses, and validates the map file
 *   3. Initializes MLX connection, window, and image buffer
 *   4. Loads wall textures from parsed paths
 *   5. Sets up event hooks for keyboard and mouse input
 *   6. Starts the main game loop
 *   7. Cleans up resources and exits on completion
 *
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return EXIT_SUCCESS on normal exit, EXIT_FAILURE on error
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_errors(ARG_USAGE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (load_and_validate_map(argv[1], &game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	print_map_grid(&game.map);
	if (init_game_data(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_textures(&game) != EXIT_SUCCESS)
	{
		cleanup_exit(&game);
		return (EXIT_FAILURE);
	}
	print_ascii_art_hello();
	setup_hooks(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_exit(&game);
	return (EXIT_SUCCESS);
}
