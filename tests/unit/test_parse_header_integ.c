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
	printf(YEL "========= map after valdiate ===========\n" RESET);
	print_map_grid(&game.map);
	cleanup_exit(&game);
	return (EXIT_SUCCESS);
}
