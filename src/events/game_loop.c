/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafroidu <pafroidu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:54:27 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 19:51:36 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if enough time has passed for next frame (60 FPS cap)
 *
 * Uses static timeval to track last frame time. On first call (tv_sec == 0),
 * always allows rendering. Subsequently enforces 16.666ms minimum between
 * frames.
 *
 * @return 1 if should render, 0 if should skip
 */
static int	should_render_frame(void)
{
	static struct timeval	last_frame;
	struct timeval			current;
	long					elapsed;

	gettimeofday(&current, NULL);
	elapsed = (current.tv_sec - last_frame.tv_sec) * 1000000
		+ (current.tv_usec - last_frame.tv_usec);
	if (elapsed >= 16666 || last_frame.tv_sec == 0)
	{
		last_frame = current;
		return (1);
	}
	return (0);
}

/**
 * @brief Main game loop - called every frame by MLX
 *
 * Executes the main rendering pipeline:
 * 1. Limits FPS to 60 for consistent movement speed
 * 2. Processes input - checks which keys are pressed and executes actions
 * 3. Renders the scene - casts WINDOWS_X rays (one per screen column)
 * 4. Displays the result - pushes image buffer to window
 *
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	game_loop(void *param)
{
	t_game			*game;
	t_key_binding	*bindings;
	int				i;

	if (!should_render_frame())
		return (EXIT_SUCCESS);
	game = (t_game *)param;
	bindings = get_key_bindings(game);
	i = 0;
	while (bindings[i].action)
	{
		if (*bindings[i].flag_ptr)
			bindings[i].action(game);
		i++;
	}
	render_frame(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (EXIT_SUCCESS);
}
