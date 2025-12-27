/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:56:37 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 14:09:09 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Program entry point for Cub3D
 *
 * Initializes game state, parses and validates the .cub file,
 * sets up graphics, loads textures, installs event hooks,
 * and enters the main rendering loop.
 *
 * @param argc Argument count
 * @param argv Argument vector
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
