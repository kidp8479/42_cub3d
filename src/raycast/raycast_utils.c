/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:09:49 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 14:09:52 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Converts wall hit position to texture column coordinate
 *
 * Maps wall_x (0.0 to 1.0) to texture column (0 to TEXTURE_WIDTH-1).
 * Clamps to valid range to handle floating point edge case where
 * wall_x might equal exactly 1.0 due to precision.
 *
 * @param wall_x Wall hit position as fractional value (0.0 to 1.0)
 * @return Texture X coordinate (0 to TEXTURE_WIDTH-1)
 */
int	calculate_tex_x(double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * TEXTURE_WIDTH);
	if (tex_x >= TEXTURE_WIDTH)
		tex_x = TEXTURE_WIDTH - 1;
	return (tex_x);
}

/**
 * @brief Retrieves a pixel color from a texture at given coordinates
 *
 * Performs boundary checks before memory access to prevent segfaults.
 * Uses MLX texture memory layout: offset = y * line_len + x * (bpp/8)
 *
 * MLX stores pixels as 32-bit integers in 0xAARRGGBB format:
 * - Casting char* to int* reads 4 bytes at once (ARGB components)
 * - Returns the complete color value as a single integer
 *
 * @param texture Pointer to the texture structure
 * @param tex_x X coordinate in texture (0 to width-1)
 * @param tex_y Y coordinate in texture (0 to height-1)
 * @return Pixel color in 0xAARRGGBB format, or TEXTURE_FALLBACK_COLOR
 * if out of bounds
 */
int	get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= texture->width)
		return (TEXTURE_FALLBACK_COLOR);
	if (tex_y < 0 || tex_y >= texture->height)
		return (TEXTURE_FALLBACK_COLOR);
	pixel = texture->addr + (tex_y * texture->line_len + tex_x
			* (texture->bpp / 8));
	return (*(int *)pixel);
}

/**
 * @brief Draws a textured wall column slice
 *
 * Maps screen Y coordinates to texture Y coordinates and samples
 * the texture for each pixel. Uses the step/tex_pos algorithm to
 * handle walls of any height, including those extending beyond screen.
 * Calculates step based on actual wall height to prevent texture squishing.
 *
 * @param game Pointer to game structure
 * @param info Drawing info containing x, draw range, line_height, wall_dir,
 * wall_x
 */
void	draw_textured_wall_slice(t_game *game, t_draw_info info)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;

	tex_x = calculate_tex_x(info.wall_x);
	step = (double)TEXTURE_HEIGHT / info.line_height;
	tex_pos = (info.draw_start - (WINDOWS_Y - info.line_height) / 2) * step;
	y = info.draw_start;
	while (y <= info.draw_end)
	{
		tex_y = (int)tex_pos;
		draw_pixel_in_buffer(game, info.x, y,
			get_texture_pixel(&game->textures[info.wall_dir], tex_x, tex_y));
		tex_pos += step;
		y++;
	}
}
