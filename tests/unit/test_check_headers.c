#include "cub3d.h"

/**
 * @file test_check_headers.c
 * @brief Unit tests for check_header_count() function.
 *
 * Tests that header count checking works correctly:
 * - Exactly 6 headers → success
 * - Less than 6 headers → fail
 * - More than 6 headers → fail
 *
 * Usage:
 *   Build: make build TEST=unit/test_check_headers.c
 *   Run:   ./bin/test_check_headers
 */
#include "cub3d.h"
#include <stdio.h>
#include <assert.h>

typedef struct s_header_count_test
{
	const char	*description;
	const char	*file_path;
	bool		expect_fail;
}	t_header_count_test;

int	main(void)
{
	int							ret;
	size_t						i;
	const t_header_count_test	tests[] = {
	{
		"Valid headers (6)",
		"../maps/test_headers/valid_header.cub",
		false
	},
	{
		"Missing header (<6)",
		"../maps/test_headers/missing_header.cub",
		true
	},
	{
		"Too many headers (>6)",
		"../maps/test_headers/too_many_headers.cub",
		true
	},
	};

	printf(YEL "=========== check_header_count Tests ===========" RESET "\n");
	i = 0;
	while (i < sizeof(tests) / sizeof(tests[0]))
	{
		printf(CYN "Test %2zu: %s\n" RESET, i + 1, tests[i].description);
		printf("Input file: %s\n", tests[i].file_path);
		ret = check_header_count(tests[i].file_path);
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
		if ((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail))
			printf(GRN "PASS\n" RESET);
		else
			printf(RED "FAIL\n" RESET);
		assert((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail));
		printf("===============================================\n");
		i++;
	}
	printf(YEL "All check_header_count tests completed!\n" RESET);
	return (0);
}
