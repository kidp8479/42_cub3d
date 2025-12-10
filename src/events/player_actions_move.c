#include "cub3d.h"

/**
  * @brief Moves player forward in current direction
  *
  * @param game Pointer to game structure
*/
void	move_forward(t_game *game)
{
	static int	frame_count = 0;

	(void)game;
	frame_count++;
	if (frame_count % 60 == 0)
		printf("DEBUG: Moving FORWARD (frame %d)\n", frame_count);
}

/**
  * @brief Moves player backward (opposite of current direction)
  *
  * @param game Pointer to game structure
*/
void	move_backward(t_game *game)
{
	static int	frame_count = 0;

	(void)game;
	frame_count++;
	if (frame_count % 60 == 0)
		printf("DEBUG: Moving BACKWARD (frame %d)\n", frame_count);
}

/**
  * @brief Strafes player to the left (perpendicular to direction)
  *
  * @param game Pointer to game structure
*/
void	strafe_left(t_game *game)
{
	static int	frame_count = 0;

	(void)game;
	frame_count++;
	if (frame_count % 60 == 0)
		printf("DEBUG: Strafing LEFT (frame %d)\n", frame_count);
}

/**
  * @brief Strafes player to the right (perpendicular to direction)
  *
  * @param game Pointer to game structure
*/
void	strafe_right(t_game *game)
{
	static int	frame_count = 0;

	(void)game;
	frame_count++;
	if (frame_count % 60 == 0)
		printf("DEBUG: Strafing RIGHT (frame %d)\n", frame_count);
}
