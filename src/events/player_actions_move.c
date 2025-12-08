#include "cub3d.h"

/**
  * @brief Moves player forward in current direction
  *
  * @param game Pointer to game structure
*/
void	move_forward(t_game *game)
{
	(void)game;
	printf("DEBUG: Moving FORWARD\n");
}

/**
  * @brief Moves player backward (opposite of current direction)
  *
  * @param game Pointer to game structure
*/
void	move_backward(t_game *game)
{
	(void)game;
	printf("DEBUG: Moving BACKWARD\n");
}

/**
  * @brief Strafes player to the left (perpendicular to direction)
  *
  * @param game Pointer to game structure
*/
void	strafe_left(t_game *game)
{
	(void)game;
	printf("DEBUG: Strafing LEFT\n");
}

/**
  * @brief Strafes player to the right (perpendicular to direction)
  *
  * @param game Pointer to game structure
*/
void	strafe_right(t_game *game)
{
	(void)game;
	printf("DEBUG: Strafing RIGHT\n");
}
