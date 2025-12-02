#include "cub3d.h"

/**
 * @brief Print an error message with optional parts.
 *
 * This function prints "Error" followed by up to three optional
 * message strings. It also applies color formatting (red + reset).
 *
 * @param p1 First part of the error message (can be NULL).
 * @param p2 Second part of the error message (can be NULL).
 * @param p3 Third part of the error message (can be NULL).
 */
void	print_errors(char *p1, char *p2, char *p3)
{
	printf("%s", RED);
	printf("Error\n");
	if (p1)
		printf("%s", p1);
	if (p2)
		printf("%s\n", p2);
	if (p3)
		printf("%s\n", p3);
	printf("\n");
	printf("%s", RESET);
}
