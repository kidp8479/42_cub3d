/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:56:37 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 20:19:37 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Program entry point for Cub3D
 *
 * Orchestrates the complete initialization sequence:
 *   1. Validates command-line arguments
 *   2. Initializes game state structure
 *   3. Parses and validates the .cub file
 *   4. Sets up graphics (MLX connection, window, image buffer)
 *   5. Loads wall textures
 *   6. Installs event hooks for keyboard/mouse input
 *   7. Enters the main rendering loop
 *
 * Exits immediately if any initialization step fails.
 *
 * @param argc Argument count (must be 2)
 * @param argv Argument vector (argv[1] = path to .cub file)
 * @return EXIT_SUCCESS on normal exit, EXIT_FAILURE on error
 *
 * @note The cleanup_exit() call at the end is never reached during normal
 *       execution, as mlx_loop() runs indefinitely until the window is closed
 */
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_errors(ARG_USAGE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	init_t_game(&game);
	if (validate_argument(argv[1]) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (parse_and_validate_cub(argv[1], &game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_graphics(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_textures(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	print_ascii_art_hello();
	print_map_grid(&game.map);
	setup_hooks(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_exit(&game);
	return (EXIT_SUCCESS);
}
