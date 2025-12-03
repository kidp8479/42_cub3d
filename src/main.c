#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		print_errors(ARG_USAGE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (validate_argument(argv[1]) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (parse_map(argv[1], &map))
		return (EXIT_FAILURE);
	print_map_grid(&map);
	free_map(&map);
	return (EXIT_SUCCESS);
}
