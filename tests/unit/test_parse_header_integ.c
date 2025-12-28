#include "cub3d.h"

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
		cleanup_exit(&game, EXIT_FAILURE);
	if (parse_and_validate_cub(argv[1], &game) != EXIT_SUCCESS)
		cleanup_exit(&game, EXIT_FAILURE);
	printf(YEL "========= map after valdiate ===========\n" RESET);
	print_map_grid(&game.map);
	cleanup_exit(&game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}