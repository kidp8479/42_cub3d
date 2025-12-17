#include "cub3d.h"

/**
 * @brief Applies a rotation to the camera using rotation matrix
 *
 * Rotates both the direction vector and the camera plane vector
 * by the given angle using 2D rotation matrix transformation.
 *
 * @param game Pointer to game structure
 * @param angle Rotation angle in radians (positive = clockwise)
 */
void	apply_camera_rotation(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

/**
 * @brief Rotates camera to the left (counter-clockwise)
 *
 * Applies rotation matrix to both direction and camera plane vectors
 * using the shared apply_camera_rotation helper function.
 *
 * @param game Pointer to game structure
 */
void	rotate_left(t_game *game)
{
	apply_camera_rotation(game, ROT_SPEED);
}

/**
 * @brief Rotates camera to the right (clockwise)
 *
 * Applies rotation matrix with negative angle (clockwise rotation)
 * using the shared apply_camera_rotation helper function.
 *
 * @param game Pointer to game structure
 */
void	rotate_right(t_game *game)
{
	apply_camera_rotation(game, -ROT_SPEED);
}
