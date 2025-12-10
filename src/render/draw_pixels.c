#include "cub3d.h"

/**
 * @brief Writes a single pixel into the image buffer
 *
 * Calculates memory offset using line_len and bpp from MLX.
 * Does not display anything until mlx_put_image_to_window is called.
 *
 * @param game Pointer to game structure containing image buffer info
 * @param x Horizontal pixel coordinate
 * @param y Vertical pixel coordinate
 * @param color Color in 0xAARRGGBB format
 */
void	draw_pixel_in_buffer(t_game *game, int x, int y, int color)
{
	char	*dest;

	dest = game->img_addr + (y * game->img_line_len + x * (game->img_bpp / 8));
	*(unsigned int *)dest = color;
}
