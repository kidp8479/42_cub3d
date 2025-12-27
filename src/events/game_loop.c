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
 * @brief Main game loop - called every frame by MLX
 *
 * Executes the main rendering pipeline:
 * 1. Processes input - checks which keys are pressed and executes actions
 * 2. Renders the scene - casts WINDOWS_X rays (one per screen column)
 * 3. Displays the result - pushes image buffer to window
 *
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	game_loop(void *param)
{
	t_game			*game;
	t_key_binding	*bindings;
	int				i;

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
