/**
 * @file test_parse_header_line.c
 * @brief Unit tests for parse_header_line() function.
 *
 * This program tests parse_header_line() with various valid and invalid
 * header lines, including texture paths and RGB values, checking proper 
 * parsing, error handling, and memory management.
 * Each test prints the input, expected result, actual result, and parsed
 * values (texture path or RGB).
 *
 * Usage:
 *   Build: make build TEST=unit/test_parse_header_line.c
 *   Run:   ./bin/test_parse_header_line
 *
 * The tests cover:
 *   - Valid texture paths (with or without extra spaces)
 *   - Valid RGB floor and ceiling values
 *   - Invalid header identifiers
 *   - Missing or empty texture paths
 *   - Non-existent texture files
 *   - RGB components out of range, too few, or too many
 *   - Ensures parse_header_line correctly interacts with get_header_entry()
 *     and parse_header_value() to indirectly test static helper functions.
 */
#include "cub3d.h"
#include <assert.h>
#include <fcntl.h>
#include <string.h>

typedef struct s_header_test
{
	const char		*description;
	char			*line;
	bool				expect_fail;
	t_header_type	id;
	int				expect_rgb[3];
	const char		*expect_path;
}	t_header_test;

/* ========================== Helpers ========================== */

static void	create_dummy_file(const char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd >= 0)
		close(fd);
}

static void	remove_dummy_file(const char *path)
{
	if (path)
		unlink(path);
}

static void	init_test_map(t_map *map)
{
	memset(map, 0, sizeof(t_map));
}

/* ========================== Printing ========================== */

static void	print_rgb(const int rgb[3])
{
	printf("[%d,%d,%d]", rgb[0], rgb[1], rgb[2]);
}

/* ========================== Test ========================== */

int	main(void)
{
	t_map				map;
	int					ret;
	size_t				i;
	const t_header_test	tests[] = {
	/* ===== Valid texture headers ===== */

	{
		"Valid North texture",
		"NO ./test_NO.xpm",
		false,
		ID_NO,
		{-1, -1, -1},
		"./test_NO.xpm"
	},
	{
		"Valid North texture with spaces",
		"NO		./test_NO.xpm	 ",
		false,
		ID_NO,
		{-1, -1, -1},
		"./test_NO.xpm"
	},
	{
		"Valid South texture",
		"SO ./test_SO.xpm",
		false,
		ID_SO,
		{-1, -1, -1},
		"./test_SO.xpm"
	},
	/* ===== Valid RGB headers ===== */
	{
		"Valid Floor RGB",
		"F 220,100,0",
		false,
		ID_FLOOR,
		{220, 100, 0},
		NULL
	},
	{
		"Valid Ceiling RGB with spaces",
		"C   10 , 20 , 30",
		false,
		ID_CEILING,
		{10, 20, 30},
		NULL
	},
	/* ===== Texture path errors ===== */
	{
		"Missing texture file",
		"WE ./does_not_exist.xpm",
		true,
		ID_WE,
		{-1, -1, -1},
		NULL
	},
	{
		"Empty texture path",
		"EA ",
		true,
		ID_EA,
		{-1, -1, -1},
		NULL
	},
	/* ===== RGB validation errors ===== */
	{
		"RGB component > 255",
		"F 300,0,0",
		true,
		ID_FLOOR,
		{-1, -1, -1},
		NULL
	},
	{
		"RGB negative value",
		"F -1,0,0",
		true,
		ID_FLOOR,
		{-1, -1, -1},
		NULL
	},
	{
		"RGB too few components",
		"F 10,20",
		true,
		ID_FLOOR,
		{-1, -1, -1},
		NULL
	},
	{
		"RGB too many components",
		"F 10,20,30,40",
		true,
		ID_FLOOR,
		{-1, -1, -1},
		NULL
	},
};
	printf(YEL "=========== parse_header_line Tests ===========" RESET "\n");
	printf("===============================================\n");
	/* create dummy texture files */
	create_dummy_file("./test_NO.xpm");
	create_dummy_file("./test_SO.xpm");
	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		// Reset map for all tests except the duplicate test
		init_test_map(&map);
		printf(CYN "Test  %2zu: %s\n" RESET, i + 1, tests[i].description);
		printf("   Input: %s\n", tests[i].line);
		printf("Expected: ");
		if (tests[i].expect_fail)
			printf(RED "FAIL" RESET "\n");
		else
			printf(GRN "SUCCESS" RESET "\n");
		ret = parse_header_line(&map, tests[i].line);
		printf("     Got: ");
		if (ret == EXIT_SUCCESS)
			printf(GRN "SUCCESS" RESET "\n");
		else
			printf(RED "FAIL" RESET "\n");
		if (!tests[i].expect_fail && ret == EXIT_SUCCESS)
		{
			if (tests[i].expect_path)
				printf("Tex path: %s\n", map.tex_paths[tests[i].id]);
			else
			{
				printf("     RGB: ");
				print_rgb(map.floor_color);
				printf("\n");
			}
		}
		if ((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail))
			printf(GRN "PASS\n" RESET);
		else
			printf(RED "FAIL\n" RESET);
		printf("===============================================\n");
		if (tests[i].expect_fail == false)
			assert(ret == EXIT_SUCCESS);
		else
			assert(ret == EXIT_FAILURE);
		i++;
		free_t_map(&map);
	}
	remove_dummy_file("./test_NO.xpm");
	remove_dummy_file("./test_SO.xpm");
	printf(YEL "All parse_header_line tests completed!" RESET "\n");
	return (0);
}
