#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		print_errors(ARG_USAGE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (validate_argument(argv[1]) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	init_data(&game);
	if (parse_map(argv[1], &game.map))
		return (EXIT_FAILURE);
	if (init_game_data(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	print_ascii_art_hello();
	print_map_grid(&game.map);
	mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
	mlx_hook(game.win, 3, 1L<<1, handle_keyrelease, &game);
	mlx_hook(game.win, 17, 0, handle_close, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
