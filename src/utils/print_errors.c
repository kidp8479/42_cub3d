#include "cub3d.h"

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
