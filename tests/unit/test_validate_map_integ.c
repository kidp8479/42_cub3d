#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	printf("Testing map: %s\n", argv[1]);
	init_data(&game);
	if (validate_argument(argv[1]) != EXIT_SUCCESS)
	{
		printf("[FAIL] validate_argument\n");
		return (EXIT_FAILURE);
	}
	if (parse_map(argv[1], &game.map) != EXIT_SUCCESS)
	{
		printf("[FAIL] parse_map\n");
		return (EXIT_FAILURE);
	}
	printf("=========initial map===========\n");
	print_map_grid(&game.map);
	printf("===============================\n");
	if (init_player(&game) != EXIT_SUCCESS)
	{
		printf("[FAIL] init_player\n");
		free_map(&game.map);
		return (EXIT_FAILURE);
	}
	print_map_grid(&game.map);
	if (check_valid_map(&game.map, &game.player) != EXIT_SUCCESS)
	{
		printf("[FAIL] check_valid_map\n");
		free_map(&game.map);
		return (EXIT_FAILURE);
	}
	printf("[OK] Map is valid\n");
	free_map(&game.map);
	return (EXIT_SUCCESS);
}
