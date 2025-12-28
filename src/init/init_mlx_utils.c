/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafroidu <pafroidu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 23:39:47 by pafroidu          #+#    #+#             */
/*   Updated: 2025/12/28 00:05:47 by pafroidu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Validates window dimensions against screen capacity
 *
 * Ensures WINDOWS_X/Y are within playable bounds and fit on screen.
 * Uses 95% screen safety margin (leaves room for taskbar/borders).
 *
 * @param mlx Valid MLX connection pointer
 * @return EXIT_SUCCESS if valid, EXIT_FAILURE otherwise
 */
int	validate_window_size(void *mlx)
{
	int	screen_w;
	int	screen_h;
	int	max_safe_w;
	int	max_safe_h;

	if (WINDOWS_X < MIN_SCREEN_WIDTH || WINDOWS_Y < MIN_SCREEN_HEIGHT)
	{
		print_errors(WIN_TOO_SMALL, NULL, NULL);
		return (EXIT_FAILURE);
	}
	mlx_get_screen_size(mlx, &screen_w, &screen_h);
	max_safe_w = screen_w * SCREEN_SAFETY_FACTOR;
	max_safe_h = screen_h * SCREEN_SAFETY_FACTOR;
	if (max_safe_w > MAX_SCREEN_WIDTH)
		max_safe_w = MAX_SCREEN_WIDTH;
	if (max_safe_h > MAX_SCREEN_HEIGHT)
		max_safe_h = MAX_SCREEN_HEIGHT;
	if (WINDOWS_X > max_safe_w || WINDOWS_Y > max_safe_h)
	{
		print_errors(WIN_TOO_LARGE, NULL, NULL);
		printf("Window: %dx%d | Screen: %dx%d | Safe max: %dx%d\n",
			WINDOWS_X, WINDOWS_Y, screen_w, screen_h, max_safe_w, max_safe_h);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
