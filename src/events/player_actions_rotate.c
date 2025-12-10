#include "cub3d.h"

/**
  * @brief Rotates camera to the left
  *
  * @param game Pointer to game structure
*/
void	rotate_left(t_game *game)
{
	static int	frame_count = 0;

	(void)game;
	frame_count++;
	if (frame_count % 60 == 0)
		printf("DEBUG: Rotating LEFT (frame %d)\n", frame_count);
}

/**
  * @brief Rotates camera to the right
  *
  * @param game Pointer to game structure
*/
void	rotate_right(t_game *game)
{
	static int	frame_count = 0;

	(void)game;
	frame_count++;
	if (frame_count % 60 == 0)
		printf("DEBUG: Rotating RIGHT (frame %d)\n", frame_count);
}
