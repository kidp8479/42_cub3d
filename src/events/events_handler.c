#include "cub3d.h"

/**
  * @brief Handles keyboard key press events
  *
  * Routes key presses to appropriate actions (movement, rotation, exit).
  *
  * @param keycode X11 keycode from event
  * @param param Pointer to game structure (void* from MLX, must cast)
  * @return 0/EXIT_SUCCESS (required by MLX)
*/
int	handle_keypress(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == XK_Escape)
		cleanup_exit(game);
	else if (keycode == XK_w || keycode == XK_W)
		move_forward(game);
	else if (keycode == XK_s || keycode == XK_S)
		move_backward(game);
	else if (keycode == XK_a || keycode == XK_A)
		strafe_left(game);
	else if (keycode == XK_d || keycode == XK_D)
		strafe_right(game);
	else if (keycode == XK_Left)
		rotate_left(game);
	else if (keycode == XK_Right)
		rotate_right(game);
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles window close button (red cross) event
 *
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return 0/EXIT_SUCCESS (required by MLX)
 */
int	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	cleanup_exit(game);
	return (EXIT_SUCCESS);
}
