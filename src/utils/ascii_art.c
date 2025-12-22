#include "cub3d.h"

/**
 * @brief Prints welcome message and game controls
 *
 * Displays ASCII art logo for "CUB3D" in green color,
 * followed by yellow-colored control instructions for the player.
 *
 * Output includes:
 *   - "CUB3D" ASCII art banner
 *   - Movement controls (WASD keys)
 *   - Camera rotation controls (arrow keys or mouse)
 *   - Exit instructions (ESC or window close button)
 */
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
