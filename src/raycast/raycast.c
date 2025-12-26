#include "cub3d.h"

/**
 * @brief Draws a vertical slice of pixels
 *
 * @param game Pointer to game structure
 * @param x Column position
 * @param start Starting Y coordinate
 * @param end Ending Y coordinate
 * @param color Color to draw
 */
static void	draw_column_slice(t_game *game, t_col column)
{
	int	y;

	y = column.start;
	while (y <= column.end)
	{
		draw_pixel_in_buffer(game, column.x, y, column.color);
		y++;
	}
}

/**
 * @brief Draws a complete column with ceiling, wall, and floor
 *
 * Draws ceiling and floor as solid colors, wall with textures.
 * Uses draw_column_slice for ceiling/floor and draw_textured_wall_slice
 * for the wall portion.
 *
 * @param game Pointer to game structure
 * @param info Drawing info containing positions, colors, wall_dir, and wall_x
 */
static void	draw_full_column(t_game *game, t_draw_info info)
{
	t_col	col;

	col.x = info.x;
	col.start = 0;
	col.end = info.draw_start - 1;
	col.color = info.ceiling;
	draw_column_slice(game, col);
	draw_textured_wall_slice(game, info);
	col.start = info.draw_end + 1;
	col.end = WINDOWS_Y - 1;
	col.color = info.floor;
	draw_column_slice(game, col);
}

/**
 * @brief Draws a vertical wall column at screen position x
 *
 * Renders a complete vertical slice: ceiling, wall, and floor.
 * Clamps to screen bounds to prevent out-of-bounds writes.
 *
 * @param game Pointer to the game structure
 * @param x Screen column position (0 to WINDOWS_X-1)
 * @param result Ray result containing wall distance, direction, and hit
 * position
 */
static void	draw_wall_column(t_game *game, int x, t_ray_result result)
{
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_draw_info	info;

	if (result.wall_dist < MIN_WALL_DISTANCE)
		result.wall_dist = MIN_WALL_DISTANCE;
	line_height = (int)(WINDOWS_Y / result.wall_dist);
	draw_start = (WINDOWS_Y - line_height) / 2;
	draw_end = draw_start + line_height - 1;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOWS_Y)
		draw_end = WINDOWS_Y - 1;
	info.x = x;
	info.draw_start = draw_start;
	info.draw_end = draw_end;
	info.line_height = line_height;
	info.ceiling = rgb_tab_to_int(game->map.ceiling_color);
	info.floor = rgb_tab_to_int(game->map.floor_color);
	info.wall_dir = result.wall_dir;
	info.wall_x = result.wall_x;
	draw_full_column(game, info);
}

/**
 * @brief Casts a single ray for one screen column and renders it
 *
 * Converts screen column x to camera space (-1.0 to +1.0),
 * calculates ray direction using linear algebra, performs raycasting via DDA
 * to find wall distance and direction, then delegates drawing to
 * draw_wall_column.
 *
 * @param game Pointer to the game structure
 * @param x Screen column index (0 to WINDOWS_X-1)
 */
static void	cast_column_ray(t_game *game, int x)
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	t_ray_result	result;

	camera_x = 2.0 * x / WINDOWS_X - 1.0;
	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	result = cast_ray(game, ray_dir_x, ray_dir_y);
	draw_wall_column(game, x, result);
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
