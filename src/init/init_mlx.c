#include "cub3d.h"

static int	init_game_connection(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		print_errors(MLX_INIT, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_game_windows(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->win = mlx_new_window(game->mlx, WINDOWS_X, WINDOWS_Y, WINDOWS_MSG);
	if (!game->win)
	{
		print_errors(WIN_INIT, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	init_game_image_buffer(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, WINDOWS_X, WINDOWS_Y);
	if (!game->img)
	{
		print_errors(IMG_INIT, NULL, NULL);
		return (EXIT_FAILURE);
	}
	game->img_addr = mlx_get_data_addr(game->img, &game->img_bpp,
			&game->img_line_len, &game->img_endian);
	if (!game->img_addr)
	{
		print_errors(IMG_DATA, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_game_data(t_game *game)
{
	if (!game)
	{
		print_errors(NULL_TGAME, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (init_game_connection(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_game_windows(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (init_game_image_buffer(game) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
