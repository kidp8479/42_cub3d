/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:55:06 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 13:55:08 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Handles mouse movement for FPS-style camera rotation
 *
 * Implements infinite rotation by recentering the cursor after each movement.
 * This prevents the cursor from hitting screen edges and allows continuous
 * rotation.
 * Only handles horizontal rotation (yaw), not vertical (pitch).
 *
 * @param x Current mouse X position in window coordinates
 * @param y Current mouse Y position in window coordinates
 * @param param Pointer to game structure (void* from MLX, must cast)
 * @return EXIT_SUCCESS
 */
int	handle_mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta_x;

	game = (t_game *)param;
	delta_x = x - game->last_mouse_x;
	if (delta_x != 0)
	{
		apply_camera_rotation(game, delta_x * MOUSE_SENSITIVITY);
		mlx_mouse_move(game->mlx, game->win, WINDOWS_X / 2, WINDOWS_Y / 2);
		game->last_mouse_x = WINDOWS_X / 2;
		game->last_mouse_y = WINDOWS_Y / 2;
		return (EXIT_SUCCESS);
	}
	game->last_mouse_x = x;
	game->last_mouse_y = y;
	return (EXIT_SUCCESS);
}
