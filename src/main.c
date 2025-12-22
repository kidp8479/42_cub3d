#include "cub3d.h"

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
	print_ascii_art_hello();
	setup_hooks(&game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_exit(&game);
	return (EXIT_SUCCESS);
}
