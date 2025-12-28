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
	init_t_game(&game);
	if (parse_map(argv[1], &game.map))
		return (EXIT_FAILURE);
	printf("=====map BEFORE=====\n");
	print_map_grid(&game.map);
	print_player_info(&game.player);
	if (init_player(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	printf("=====map AFTER=====\n");
	print_map_grid(&game.map);
	print_player_info(&game.player);
	free_t_map(&game.map);
	return (EXIT_SUCCESS);
}
