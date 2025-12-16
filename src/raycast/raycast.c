#include "cub3d.h"

/**
 * @brief Draws a vertical wall column at screen position x
 *
 * Draws a centered vertical line from draw_start to draw_end.
 * Clamps to screen bounds to prevent out-of-bounds writes.
 *
 * @param game Pointer to the game structure
 * @param x Screen column position (0 to WINDOWS_X-1)
 * @param line_height Height of the wall line in pixels
 */
static void	draw_wall_column(t_game *game, int x, int line_height)
{
	int	draw_start;
	int	draw_end;
	int	y;

	draw_start = (WINDOWS_Y - line_height) / 2;
	draw_end = draw_start + line_height - 1;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOWS_Y)
		draw_end = WINDOWS_Y - 1;
	y = draw_start;
	while (y <= draw_end)
	{
		draw_pixel_in_buffer(game, x, y, 0xFF0000);
		y++;
	}
}

/**
 * @brief Casts a single ray for one screen column and renders it
 *
 * Converts screen column x to camera space, calculates ray direction,
 * performs raycasting to find wall distance, and draws the wall slice.
 *
 * @param game Pointer to the game structure
 * @param x Screen column index (0 to WINDOWS_X-1)
 */
static void	cast_column_ray(t_game *game, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_distance;
	int		line_height;

	camera_x = ((2.0 * x) / WINDOWS_X) - 1.0;
	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	wall_distance = cast_ray(game, ray_dir_x, ray_dir_y);
	line_height = (int)(WINDOWS_Y / wall_distance);
	draw_wall_column(game, x, line_height);
}

/**
  * @brief Renders a complete frame with full raycasting
  *
  * Main rendering loop that casts one ray per screen column
  * (WINDOWS_X rays total).
  *
  * @param game Pointer to the game structure
*/
void	render_frame(t_game *game)
{
	int		x;

	x = 0;
	while (x < WINDOWS_X)
	{
		cast_column_ray(game, x);
		x++;
	}
}

