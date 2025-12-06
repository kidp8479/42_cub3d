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
	print_map_grid(&game.map);
	free_map(&game.map);
	return (EXIT_SUCCESS);
}
