#include "cub3d.h"

/**
 * test_valid_arguments - tests files that should pass validation
 */
void	test_valid_arguments(void)
{
	printf(GRN "\n=== VALID FILES ===\n" RESET);

	printf("\n[1] maps/valid/basic_map.cub\n");
	printf("  Result: %s\n", validate_argument("maps/valid/basic_map.cub") == EXIT_SUCCESS ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[2] maps/valid/ab.cub (edge: 6 chars, just above minimum)\n");
	printf("  Result: %s\n", validate_argument("maps/valid/ab.cub") == EXIT_SUCCESS ? GRN "PASS" RESET : RED "FAIL" RESET);
}

/**
 * test_invalid_arguments - tests files that should fail validation
 */
void	test_invalid_arguments(void)
{
	printf(RED "\n=== INVALID FILES ===\n" RESET);

	printf("\n[1] NULL pointer\n");
	printf("  Result: %s\n", validate_argument(NULL) == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[2] Empty string\n");
	printf("  Result: %s\n", validate_argument("") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[3] maps/invalid/.hidden.cub (hidden file)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/.hidden.cub") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[4] maps/invalid/a.cu (too short: 4 chars)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/a.cu") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[5] maps/invalid/invalid.ber (wrong extension)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/invalid.ber") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[6] maps/invalid/test.CUB (uppercase extension)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/test.CUB") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[7] maps/invalid/testcub (no extension)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/testcub") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[8] maps/invalid/folder.cub (is a directory)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/folder.cub") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	printf("\n[9] maps/nonexistent.cub (file doesn't exist)\n");
	printf("  Result: %s\n", validate_argument("maps/nonexistent.cub") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET);

	/* printf("\n[10] maps/invalid/noperm.cub (no permissions)\n");
	printf("  Result: %s\n", validate_argument("maps/invalid/noperm.cub") == EXIT_FAILURE ? GRN "PASS" RESET : RED "FAIL" RESET); */
}

int	main(void)
{

	printf(MAG "FILE VALIDATION TESTS - cub3D\n" RESET);

	test_valid_arguments();
	test_invalid_arguments();

	return (0);
}
