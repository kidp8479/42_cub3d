#include "cub3d.h"

void	tests_basename(void)
{
	printf(MAG "\n=== TEST GET_FILE_BASENAME ===\n" RESET);
	printf("Test 1: %s\n", get_file_basename("/home/user/test.cub"));
	printf("Test 2: %s\n", get_file_basename("./maps/test.cub"));
	printf("Test 3: %s\n", get_file_basename("test.cub"));
	printf("Test 4: %s\n", get_file_basename("maps/.hidden.cub"));
}

/* sorry for the extra /n when the test prints an ERROR, I can't predict if we
need extra \n or not */
void tests_filename(void)
{
	int result;

	printf(MAG "\n=== TEST IS_VALID_FILENAME ===\n" RESET);

	// Test 1
	printf("\n[Test 1] test.cub\n");
	result = is_valid_filename("test.cub");
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);

	// Test 2
	printf("\n[Test 2] ./maps/test.cub\n");
	result = is_valid_filename("./maps/test.cub");
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);

	// Test 3
	printf("\n[Test 3] .hidden.cub (should fail)\n");
	result = is_valid_filename(".hidden.cub");
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);

	// Test 4
	printf("\n[Test 4] a.cub (exactly 5 chars)\n");
	result = is_valid_filename("a.cub");
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);

	// Test 5
	printf("\n[Test 5] ab.cu (too short)\n");
	result = is_valid_is_valid_filename("ab.cu");
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);

	// Test 6
	printf("\n[Test 6] test.ber (wrong extension)\n");
	result = is_valid_is_valid_filename("test.ber");
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);

	// Test 7
	printf("\n[Test 7] NULL\n");
	result = is_valid_is_valid_filename(NULL);
	printf("  → Result: %s%d%s\n", result ? GRN : RED, result, RESET);
}

int main(void)
{
	tests_basename();
	tests_filename();
	return (0);
}
