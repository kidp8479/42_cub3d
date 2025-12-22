/**
 * @file test_parse_header_duplicate.c
 * @brief Unit test for detecting duplicate header lines in
 * parse_header_line().
 *
 * This program specifically tests the behavior of parse_header_line() when the
 * same header is parsed twice. It ensures that:
 *   - The first occurrence of a valid header line succeeds.
 *   - A second occurrence of the same header line triggers a failure 
 *     (duplicate header detection).
 *
 * Usage:
 *   Build: make build TEST=unit/test_parse_header_duplicate.c
 *   Run:   ./bin/test_parse_header_duplicate
 *
 * The test creates temporary dummy texture files to satisfy validation checks.
 * Memory is properly freed after the test.
 */
#include "cub3d.h"
#include <stdio.h>
#include <assert.h>

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

int	main(void)
{
	t_map	map;
	int		ret;

	printf(CYN"=== Parse header line duplicate header Test ===\n\n" RESET);
	printf("=================================================\n");
	create_dummy_file("./test_NO.xpm");
	// Initialize map
	init_test_map(&map);
    // First parse - should succeed
	ret = parse_header_line(&map, "NO ./test_NO.xpm");
	printf("First parse: Input 'NO ./test_NO.xpm'\n");
	printf("Expected: %sSUCCESS%s\n", GRN, RESET);
	printf("Got: ");
	if (ret == EXIT_SUCCESS)
		printf(GRN "SUCCESS\n" RESET);
	else
		printf(RED "FAIL\n" RESET);
	assert(ret == EXIT_SUCCESS);
	printf("=================================================\n");
	// Second parse - should fail (duplicate)
	ret = parse_header_line(&map, "NO ./test_NO.xpm");
	printf("Second parse: Input 'NO ./test_NO.xpm'\n");
	printf("Expected: %sFAIL%s\n", RED, RESET);
	printf("Got: ");
	if (ret == EXIT_FAILURE)
		printf("%sFAIL%s %s(PASS)%s\n", RED, RESET, GRN, RESET);
	else
		printf("%sSUCCESS%s %s(FAIL)%s\n", GRN, RESET, RED, RESET);
	assert(ret == EXIT_FAILURE);
	free_t_map(&map);
	remove_dummy_file("./test_NO.xpm");
	printf(CYN "\nDuplicate header test completed!\n" RESET);
	return (0);
}
