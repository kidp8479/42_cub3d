#include "cub3d.h"

void	print_ascii_art_hello(void)
{
	printf("Welcome to\n");
	printf(BR_GRN);
	printf(" ██████╗██╗   ██╗██████╗ ██████╗ ██████╗\n");
	printf("██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n");
	printf("██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n");
	printf("██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n");
	printf("╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n");
	printf(" ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝\n");
	printf(RESET);
	printf(BR_YEL);
	printf("use WASD to move - left/right arrow (or mouse) to rotate camera\n");
	printf("press ESC or click the window cross to exit game\n\n");
	printf(RESET);
}
