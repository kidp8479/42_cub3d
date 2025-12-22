/**
 * @file test_parse_header.c
 * @brief Unit tests for the parse_header() function in cub3d.
 *
 * This test program validates the parsing of .cub file headers.
 * It checks:
 *   - All six headers present and correctly parsed
 *   - Duplicate headers
 *   - Invalid RGB values (too few, too many, or non-integer)
 *   - Texture file existence and path validity
 *   - Correct detection of map start line
 *   - Handling of empty lines
 *
 * Usage:
 *   Build: make build TEST=unit/test_parse_header.c
 *   Run:   ./bin/test_parse_header
 *
 * Each test uses a real .cub file, prints expected vs actual results,
 * and uses assertions to verify correct behavior.
 */
#include "cub3d.h"
#include <stdio.h>
#include <assert.h>

#define EXPECTED_MAP_START_LINE 8

typedef struct s_header_test
{
	const char	*description;
	const char	*file_path;
	bool		expect_fail;
	int			expected_map_start_line;
}	t_header_test;

int	main(void)
{
	t_map				map;
	int					ret;
	size_t				i;
	const t_header_test	tests[] = {
	{
		"Valid map file",
		"../maps/test_headers/valid_header.cub",
		false,
		EXPECTED_MAP_START_LINE
	},
	{
		"Duplicate header",
		"../maps/test_headers/duplicate_headers.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"Invalid floor value",
		"../maps/test_headers/invalid_value_floor.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"Invalid ceiling value",
		"../maps/test_headers/invalid_value_ceiling.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"Texture file missing",
		"../maps/test_headers/texture_missing.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"Texture invalid path",
		"../maps/test_headers/texture_bad_path.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"RGB missing component",
		"../maps/test_headers/rgb_missing_component.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"RGB extra component",
		"../maps/test_headers/rgb_extra_component.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"RGB non integer",
		"../maps/test_headers/rgb_non_integer.cub",
		true,
		EXPECTED_MAP_START_LINE
	},
	{
		"Empty lines",
		"../maps/test_headers/empty_lines.cub",
		false,
		EXPECTED_MAP_START_LINE + 6
	},
	{
		"Header ID in random order",
		"../maps/test_headers/header_id_random_order.cub",
		false,
		EXPECTED_MAP_START_LINE
	},
	};

	printf(YEL "================ parse_header Tests =================" RESET "\n");
	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		memset(&map, 0, sizeof(t_map));
		printf(CYN "Test %2zu: %s\n" RESET, i + 1, tests[i].description);
		printf("Input file: %s\n", tests[i].file_path);
		ret = parse_header(tests[i].file_path, &map);
		printf("Expected: ");
		if (tests[i].expect_fail)
			printf(RED "FAIL\n" RESET);
		else
			printf(GRN "SUCCESS\n" RESET);
		printf("     Got: ");
		if (ret == EXIT_SUCCESS)
			printf(GRN "SUCCESS\n" RESET);
		else
			printf(RED "FAIL\n" RESET);
		if (!tests[i].expect_fail && ret == EXIT_SUCCESS)
		{
			printf("Expected map start line: %d\n", tests[i].expected_map_start_line);
			printf("     Got Map start line: %d\n", map.map_start_line);
			assert(map.map_start_line == tests[i].expected_map_start_line);
		}
		if ((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail))
			printf(GRN "PASS\n" RESET);
		else
			printf(RED "FAIL\n" RESET);
		assert((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail));
		printf("====================================================\n");
		i++;
		free_t_map(&map);
	}
	printf(YEL "All parse_header tests completed!\n" RESET);
	return (0);
}
