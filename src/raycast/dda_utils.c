#include "cub3d.h"

/**
 * @brief Checks if ray hit a wall or went out of bounds
 *
 * Performs bounds checking before grid access to prevent segfaults
 * and infinite loops if ray escapes map boundaries.
 *
 * @param game Pointer to the game structure (contains the map)
 * @param ray Pointer to the ray structure
 * @return true if hit wall or out of bounds, false otherwise
 */
bool	check_hit(t_game *game, t_ray *ray)
{
	if (ray->map_x < 0 || ray->map_x >= game->map.width)
		return (true);
	if (ray->map_y < 0 || ray->map_y >= game->map.height)
		return (true);
	if (game->map.grid[ray->map_y][ray->map_x] == '1')
		return (true);
	return (false);
}

/**
 * @brief Calculates the exact hit position on the wall (0.0 to 1.0)
 *
 * Determines where on the wall surface the ray hit, needed for
 * texture mapping. The formula depends on whether a vertical or
 * horizontal wall was hit.
 *
 * @param ray Pointer to the ray structure
 * @param pos_x Player's X position
 * @param pos_y Player's Y position
 * @param wall_dist Perpendicular distance to the wall
 * @return Wall hit position as a value between 0.0 and 1.0
*/
double	calculate_wall_x(t_ray *ray, double pos_x, double pos_y,
		double wall_dist)
{
	double	wall_x;

	if (ray->side == VERTICAL_WALL)
		wall_x = pos_y + wall_dist * ray->dir_y;
	else
		wall_x = pos_x + wall_dist * ray->dir_x;
	wall_x = wall_x - floor(wall_x);
	return (wall_x);
}

/**
 * @brief Determines wall direction from ray step and side
 *
 * Uses ray side (vertical/horizontal) and step direction
 * to determine which cardinal direction wall faces.
 * Returns texture index (NO/SO/WE/EA) matching texture array.
 *
 * @param ray Pointer to ray structure
 * @return Wall direction (NO, SO, WE, or EA)
 */
int	get_wall_direction(t_ray *ray)
{
	if (ray->side == VERTICAL_WALL)
	{
		if (ray->step_x > 0)
			return (ID_EA);
		return (ID_WE);
	}
	if (ray->step_y > 0)
		return (ID_SO);
	return (ID_NO);
}
