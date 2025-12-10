#include "cub3d.h"

/**
 * @brief Handles mouse movement for horizontal camera rotation (stub)
 *
 * Detects horizontal mouse movement and logs rotation direction.
 * Only handles left/right rotation (yaw), not up/down (pitch).
 * Currently just logs debug messages, actual rotation logic to be implemented.
 *
 * @param x Current mouse X position in window coordinates
 * @param y Current mouse Y position in window coordinates
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	handle_mouse_move(int x, int y, void *param)
{
	static int	frame_count_left = 0;
	static int	frame_count_right = 0;
	t_game		*game;
	int			delta_x;

	game = (t_game *)param;
	delta_x = x - game->last_mouse_x;
	if (delta_x > 0)
	{
		frame_count_right++;
		if (frame_count_right % 60 == 0)
			printf("DEBUG: Mouse rotating RIGHT (frame %d)\n",
				frame_count_right);
	}
	else if (delta_x < 0)
	{
		frame_count_left++;
		if (frame_count_left % 60 == 0)
			printf("DEBUG: Mouse rotating LEFT (frame %d)\n", frame_count_left);
	}
	game->last_mouse_x = x;
	game->last_mouse_y = y;
	return (EXIT_SUCCESS);
}
