#include "cub3d.h"

int	handle_keypress(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == XK_Escape)
		cleanup_exit(game);
	else if (keycode == XK_w || keycode == XK_W)
		game->keys.w_pressed = true;
	else if (keycode == XK_s || keycode == XK_S)
		game->keys.s_pressed = true;
	else if (keycode == XK_a || keycode == XK_A)
		game->keys.a_pressed = true;
	else if (keycode == XK_d || keycode == XK_D)
		game->keys.d_pressed = true;
	else if (keycode == XK_Left)
		game->keys.left_arrow_pressed = true;
	else if (keycode == XK_Right)
		game->keys.right_arrow_pressed = true;
	return (EXIT_SUCCESS);
}

int	handle_keyrelease(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == XK_w || keycode == XK_W)
		game->keys.w_pressed = false;
	else if (keycode == XK_s || keycode == XK_S)
		game->keys.s_pressed = false;
	else if (keycode == XK_a || keycode == XK_A)
		game->keys.a_pressed = false;
	else if (keycode == XK_d || keycode == XK_D)
		game->keys.d_pressed = false;
	else if (keycode == XK_Left)
		game->keys.left_arrow_pressed = false;
	else if (keycode == XK_Right)
		game->keys.right_arrow_pressed = false;
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

int	game_loop(void *param)
{
	t_game	*game = (t_game *)param;

	if (game->keys.w_pressed)
		move_forward(game);
	if (game->keys.s_pressed)
		move_backward(game);
	if (game->keys.a_pressed)
		strafe_left(game);
	if (game->keys.d_pressed)
		strafe_right(game);
	if (game->keys.left_arrow_pressed)
		rotate_left(game);
	if (game->keys.right_arrow_pressed)
		rotate_right(game);
	return (EXIT_SUCCESS);
}
