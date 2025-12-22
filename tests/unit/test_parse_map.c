/**
 * @file test_parse_map.c
 * @brief Unit tests for the parse_map() function in cub3d.
 *
 * This test program validates map parsing logic after headers
 * have been processed.
 * It checks:
 *   - Correct map width calculation (max line length)
 *   - Correct map height calculation
 *   - Proper padding of map lines with spaces
 *   - Handling of maps with and without headers
 *   - Correct use of map_start_line
 *
 * Usage:
 *   Build: make build TEST=unit/test_parse_map.c
 *   Run:   ./bin/test_parse_map
 *
 * Each test uses a real .cub file, prints expected vs actual results,
 * and uses assertions to verify correct behavior.
 */
#include "cub3d.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct s_map_test
{
	const char	*description;
	const char	*file_path;
	int			expected_width;
	int			expected_height;
	int			map_start_line;
}	t_map_test;

int	main(void)
{
	int					y;
	size_t				len;
	t_game				game;
	size_t				i;
	const t_map_test	tests[] = {
	{
		"map only 3x5",
		"../maps/test_maps/valid_3x5.cub",
		3, 5,
		0
	},
	{
		"Valid map with padding",
		"../maps/test_cub_files/valid_map.cub",
		33, 14,
		8
	},
	{
		"Map no headers",
		"../maps/test_cub_files/map_no_headers.cub",
		33, 14,
		0
	},
	};

	printf(YEL "================ parse_map Tests =================\n" RESET);
	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		memset(&game, 0, sizeof(t_game));
		game.map.map_start_line = tests[i].map_start_line;
		printf("Test %zu: %s\n", i + 1, tests[i].description);
		assert(parse_map(tests[i].file_path, &game.map) == EXIT_SUCCESS);
		printf("Expected width: %d, Got: %d\n", tests[i].expected_width, game.map.width);
		printf("Expected height: %d, Got: %d\n", tests[i].expected_height, game.map.height);
		assert(game.map.width == tests[i].expected_width);
		assert(game.map.height == tests[i].expected_height);
		y = 0;
		while (y < game.map.height)
		{
			len = strlen(game.map.grid[y]);
			assert(len == (size_t)game.map.width);
			y++;
		}
		printf("PASS\n");
		free_t_map(&game.map);
		i++;
		printf("================================================\n");
	}
	printf(YEL "All parse_map tests completed!\n" RESET);
	return (0);
}
