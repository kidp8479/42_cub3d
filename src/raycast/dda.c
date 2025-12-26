#include "cub3d.h"

/**
 * @brief Calculates the delta distances for X and Y
 *
 * Delta distance is the distance the ray must travel to cross one grid line.
 * Uses 1e30 for zero directions to avoid division by zero.
 *
 * @param ray Pointer to the ray structure
 */
static void	calculate_delta_dist(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

/**
 * @brief Calculates the initial side distances and step direction
 *
 * Side distance is how far the ray must travel to reach the first grid line.
 * Step direction indicates whether we move +1 or -1 in the grid.
 *
 * @param ray Pointer to the ray structure
 * @param pos_x Player's X position
 * @param pos_y Player's Y position
 */
static void	calculate_side_dist(t_ray *ray, double pos_x, double pos_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pos_y) * ray->delta_dist_y;
	}
}

/**
 * @brief Performs the DDA algorithm to find the wall
 *
 * Steps through the grid line by line until hitting a wall.
 * Updates ray.side to indicate if wall is vertical (0) or horizontal (1).
 *
 * @param game Pointer to the game structure (contains the map)
 * @param ray Pointer to the ray structure
 */
static void	perform_dda(t_game *game, t_ray *ray)
{
	bool	hit;

	hit = false;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = VERTICAL_WALL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = HORIZONTAL_WALL;
		}
		hit = check_hit(game, ray);
	}
}

/**
 * @brief Calculates the perpendicular wall distance
 *
 * Uses perpendicular distance (not euclidean) to avoid fisheye effect.
 * Subtracts the last delta_dist that was added in the DDA loop.
 *
 * @param ray Pointer to the ray structure
 * @return The perpendicular distance to the wall
 */
static double	calculate_wall_distance(t_ray *ray)
{
	double	perp_wall_dist;

	if (ray->side == VERTICAL_WALL)
		perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	return (perp_wall_dist);
}

/**
 * @brief Casts a ray and returns all raycasting results
 *
 * This is the main DDA function that initializes the ray and finds
 * the distance to the nearest wall, its direction, and exact hit position.
 *
 * @param game Pointer to the game structure
 * @param ray_dir_x X component of the ray direction
 * @param ray_dir_y Y component of the ray direction
 * @return t_ray_result containing wall_dist, wall_dir, and wall_x
 */
t_ray_result	cast_ray(t_game *game, double ray_dir_x, double ray_dir_y)
{
	t_ray			ray;
	t_ray_result	result;

	// initialize ray direction and map position
	ray.dir_x = ray_dir_x;
	ray.dir_y = ray_dir_y;
	ray.map_x = (int)game->player.pos_x;
	ray.map_y = (int)game->player.pos_y;
	// calculate distances
	calculate_delta_dist(&ray);
	calculate_side_dist(&ray, game->player.pos_x, game->player.pos_y);
	// perform DDA to find wall
	perform_dda(game, &ray);
	// determine wall direction and calculate distances
	result.wall_dir = get_wall_direction(&ray);
	result.wall_dist = calculate_wall_distance(&ray);
	// calculate exact hit position on wall for texture mapping
	result.wall_x = calculate_wall_x(&ray, game->player.pos_x,
			game->player.pos_y, result.wall_dist);
	return (result);
}
