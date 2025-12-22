/**
 * @file test_parse_rgb.c
 * @brief Unit tests for parse_rgb() function.
 *
 * This program tests parse_rgb() with various valid and invalid
 * RGB input strings, checking proper parsing and error handling.
 * Each test prints the input, expected result, and actual result.
 *
 * Usage:
 *   Build: make build TEST=unit/test_parse_rgb.c
 *   Run:   ./bin/test_parse_rgb
 *
 * The tests cover:
 *   - Normal valid inputs
 *   - Edge values (0, 255)
 *   - Values out of range (<0, >255)
 *   - Too few or too many components
 *   - Non-integer or empty input
 *   - Inputs with extra whitespace
 */
#include "cub3d.h"
#include <assert.h>
#include <stdio.h>

typedef struct s_rgb_test
{
	const char	*input;
	int			expected[3];
	int			expect_fail;
}	t_rgb_test;

static void	print_rgb(const int rgb[3])
{
	printf("[%d, %d, %d]", rgb[0], rgb[1], rgb[2]);
}

int	main(void)
{
	int					rgb[3];
	int					ret;
	size_t				i;
	size_t				num_tests;
	const t_rgb_test	tests[] = {
	{"255,128,0",       {255,128,0},   0}, //Normal case, valid RGB
	{"0,0,0",           {0,0,0},       0}, //Min values, valid RGB
	{"255,255,255",     {255,255,255}, 0}, //Max values, valid RGB
	{"300,128,0",       {0,0,0},       1}, //component > 255, fail
	{"255,-1,0",        {0,0,0},       1}, //component < 0, fail
	{"255,128",         {0,0,0},       1}, //too few components, fail
	{"255,128,0,0",     {0,0,0},       1}, //too many components, fail
	{"abc,128,0",       {0,0,0},       1}, //non-integer input, fail
	{"  255 , 128 ,0 ", {255,128,0},   0}, //spaces around values, valid
	{"",                {0,0,0},       1}, //empty string, fail
	};
	// feel free to add more test cases to the table
	num_tests = sizeof(tests) / sizeof(tests[0]);
	printf("=== parse_rgb Tests ===\n\n");
	i = 0;
	while (i < num_tests)
	{
		ret = parse_rgb(tests[i].input, rgb);
		printf(CYN "Test %2zu: \n" RESET, i + 1);
		printf("Input: %s\n", tests[i].input);
		printf("Expected: ");
		if (!tests[i].expect_fail)
			print_rgb(tests[i].expected);
		else
			printf(RED "FAIL" RESET);
		printf("\n     Got: ");
		if (ret == EXIT_SUCCESS)
			print_rgb(rgb);
		else
			printf(RED "FAIL" RESET);
		if ((ret == EXIT_SUCCESS && !tests[i].expect_fail)
			|| (ret == EXIT_FAILURE && tests[i].expect_fail))
			printf(GRN "\nPASS" RESET);
		else
		{
			printf(RED "\nFAIL" RESET);
			if (ret == EXIT_SUCCESS)
				print_rgb(rgb);
		}
		printf("\n===============================================\n");
		if (!tests[i].expect_fail)
			assert(ret == EXIT_SUCCESS
				&& rgb[0] == tests[i].expected[0]
				&& rgb[1] == tests[i].expected[1]
				&& rgb[2] == tests[i].expected[2]);
		else
			assert(ret == EXIT_FAILURE);
		i++;
	}
	printf("\nAll parse_rgb tests completed!\n");
	return (0);
}
