#include "cub3d.h"

/**
 * @brief Draws a vertical line on the screen
 *
 * Draws a vertical line from y_start to y_end at column x with the given color.
 * Includes bounds checking to prevent out-of-bounds writes.
 *
 * @param game Pointer to the game structure
 * @param x X coordinate (column) where to draw
 * @param y_start Starting Y coordinate (top of line)
 * @param y_end Ending Y coordinate (bottom of line)
 * @param color Color in RGB format (0xRRGGBB)
 */
static void	draw_vertical_line(t_game *game, int x, int y_start, int y_end,
		int color)
{
	int	y;

	// clamp y_start to valid range
	if (y_start < 0)
		y_start = 0;
	// clamp y_end to valid range
	if (y_end >= WINDOWS_Y)
		y_end = WINDOWS_Y - 1;
	// draw each pixel in the vertical line
	y = y_start;
	while (y <= y_end)
	{
		// x is already validated (always WINDOWS_X / 2)
		// y is clamped, so no need for bounds check here
		draw_pixel_in_buffer(game, x, y, color);
		y++;
	}
}

/**
 * @brief Renders a single ray at the center of the screen
 *
 * This function:
 * 1. Casts ONE ray straight ahead (player direction)
 * 2. Calculates the wall distance
 * 3. Draws ONE vertical line at screen center (x = WINDOWS_X / 2)
 *
 * @param game Pointer to the game structure
 */
void	render_single_ray(t_game *game)
{
	double	wall_distance;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		side;

	wall_distance = cast_ray(game, game->player.dir_x, game->player.dir_y, &side);
	line_height = (int)(WINDOWS_Y / wall_distance);
	draw_start = (WINDOWS_Y - line_height) / 2;
	draw_end = draw_start + line_height - 1;
	draw_vertical_line(game, WINDOWS_X / 2, draw_start, draw_end, 0xFF0000);
}
