#include "cub3d.h"

/**
 * @brief Returns wall color based on direction
 *
 * @param wall_dir Wall direction (NORTH/SOUTH/EAST/WEST)
 * @return Color in 0xRRGGBB format
 */
static int	get_wall_color(int wall_dir)
{
	if (wall_dir == NORTH)
		return (0xFF0000);
	else if (wall_dir == SOUTH)
		return (0x00FF00);
	else if (wall_dir == EAST)
		return (0x0000FF);
	else
		return (0xFFFF00);
}

/**
 * @brief Draws a vertical slice of pixels
 *
 * @param game Pointer to game structure
 * @param x Column position
 * @param start Starting Y coordinate
 * @param end Ending Y coordinate
 * @param color Color to draw
 */
static void	draw_column_slice(t_game *game, int x, int start, int end,
	int color)
{
	int	y;

	y = start;
	while (y <= end)
	{
		draw_pixel_in_buffer(game, x, y, color);
		y++;
	}
}

/**
 * @brief Draws a vertical wall column at screen position x
 *
 * Renders a complete vertical slice: ceiling, wall, and floor.
 * Clamps to screen bounds to prevent out-of-bounds writes.
 *
 * @param game Pointer to the game structure
 * @param x Screen column position (0 to WINDOWS_X-1)
 * @param wall_distance Perpendicular distance to the wall
 * @param wall_dir Wall direction (0=NORTH, 1=SOUTH, 2=EAST, 3=WEST)
 */
static void	draw_wall_column(t_game *game, int x, double wall_distance,
	int wall_dir)
{
	int	line_height;
	int	draw_start;
	int	draw_end;

	if (wall_distance < 0.001)
		wall_distance = 0.001;
	line_height = (int)(WINDOWS_Y / wall_distance);
	draw_start = (WINDOWS_Y - line_height) / 2;
	draw_end = draw_start + line_height - 1;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WINDOWS_Y)
		draw_end = WINDOWS_Y - 1;
	draw_column_slice(game, x, 0, draw_start - 1, game->map.ceiling_color);
	draw_column_slice(game, x, draw_start, draw_end, get_wall_color(wall_dir));
	draw_column_slice(game, x, draw_end + 1, WINDOWS_Y - 1,
		game->map.floor_color);
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
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	wall_distance;
	int		wall_dir;

	camera_x = 2.0 * x / WINDOWS_X - 1.0;
	ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	wall_distance = cast_ray(game, ray_dir_x, ray_dir_y, &wall_dir);
	draw_wall_column(game, x, wall_distance, wall_dir);
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
