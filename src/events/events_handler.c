#include "cub3d.h"

/**
 * @brief Returns an array of key bindings mapping keycodes to actions
 *
 * This function returns a static array that maps X11 keycodes to their
 * corresponding action functions and key state flags.
 * Initializes the bindings only once on first call for efficiency.
 *
 * @param game Pointer to game structure to access key flags
 * @return Pointer to a static array of key bindings (NULL-terminated)
 */
t_key_binding	*get_key_bindings(t_game *game)
{
	static t_key_binding	bindings[7];
	static bool				initialized = false;

	if (!initialized)
	{
		bindings[0] = (t_key_binding){XK_w, move_forward, &game->keys.w_pressed};
		bindings[1] = (t_key_binding){XK_s, move_backward, &game->keys.s_pressed};
		bindings[2] = (t_key_binding){XK_a, strafe_left, &game->keys.a_pressed};
		bindings[3] = (t_key_binding){XK_d, strafe_right, &game->keys.d_pressed};
		bindings[4] = (t_key_binding){XK_Left, rotate_left,
			&game->keys.left_arrow_pressed};
		bindings[5] = (t_key_binding){XK_Right, rotate_right,
			&game->keys.right_arrow_pressed};
		bindings[6] = (t_key_binding){0, NULL, NULL};
		initialized = true;
	}
	return (bindings);
}

/**
 * @brief Handles key press events using function pointers
 *
 * Iterates through key bindings and sets the corresponding flag to true
 * when a registered key is pressed.
 *
 * @param keycode X11 keycode of the pressed key
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	handle_keypress(int keycode, void *param)
{
	t_game				*game;
	const t_key_binding	*bindings;
	int					i;

	game = (t_game *)param;
	if (keycode == XK_Escape)
		cleanup_exit(game);
	bindings = get_key_bindings(game);
	i = 0;
	while (bindings[i].action)
	{
		if (bindings[i].keycode == keycode)
		{
			*bindings[i].flag_ptr = true;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Handles key release events using function pointers
 *
 * Iterates through key bindings and sets the corresponding flag to false
 * when a registered key is released.
 *
 * @param keycode X11 keycode of the released key
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	handle_keyrelease(int keycode, void *param)
{
	t_game				*game;
	t_key_binding		*bindings;
	int					i;

	game = (t_game *)param;
	bindings = get_key_bindings(game);
	i = 0;
	while (bindings[i].action)
	{
		if (bindings[i].keycode == keycode)
		{
			*bindings[i].flag_ptr = false;
			return (EXIT_SUCCESS);
		}
		i++;
	}
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
