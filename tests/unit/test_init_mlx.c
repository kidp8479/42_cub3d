#include "cub3d.h"

/**
 * @brief Test MLX initialization and pixel drawing
 *
 * Tests the complete MLX init pipeline:
 * 1. init_game_data() - Creates connection, window, and image buffer
 * 2. draw_pixel_in_buffer() - Draws a 50x50 green square at origin
 * 3. Displays the buffer and enters event loop
 *
 * Expected result: Window opens with green square in top-left corner
 * note:
 * - you'll have to kill the window by ctrl+c in your terminal because no
 * events are implemented yet
 * - no clean up is done in this test, it's not making much sense without
 * having the events set up
 */
/* int	main(void)
{
	t_game	game;
	int		i;		// iterator rows
	int		j;		// iterator columns

	// initialize all MLX components (connection, window, image buffer)
	if (init_game_data(&game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	// draw a 50x50 green square at position (0, 0)
	// color: 0x0000FF00 = Green (0xAARRGGBB format)
	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			draw_pixel_in_buffer(&game, j, i, 0x0000FF00);
			j++;
		}
		i++;
	}

	// copy buffered image to the window at position (0, 0)
	// this is when the image becomes visible to the user
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);

	// launch event loop (waits for keyboard/mouse/window events - NOT CODED YET)
	// this function never returns - infinite loop
	// close window manually to exit (no cleanup in this test)
	mlx_loop(game.mlx);

	return (0);
} */
