#include "cub3d.h"

/**
 * @brief Checks if a character represents a player orientation.
 *
 * Compares the character against the defined PLAYER string ("NSEW").
 *
 * @param c Character to check.
 * @return true if c is 'N', 'S', 'E', or 'W', false otherwise.
 */
static bool	is_player(char c)
{
	int	i;

	i = 0;
	while (PLAYER[i])
	{
		if (PLAYER[i] == c)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Returns a lookup table for player orientations.
 *
 * This table associates the player’s starting orientation character
 * ('N', 'S', 'E', 'W') with the corresponding direction vector and
 * camera plane vector used by the raycasting engine.
 *
 * The direction vectors represent the unit vector pointing toward
 * where the player initially faces. The camera plane vectors are
 * perpendicular to the direction vectors and determine the field of
 * view. The chosen magnitude (±0.66) corresponds to a FOV of ~66°,
 * which is the value used in the original Wolfenstein 3D formulation
 * and is standard in basic raycasting engines.
 *
 * @return Pointer to a static array of 4 t_orientation elements.
 */
static const t_orientation	*get_orientation(void)
{
	static const t_orientation	orient[4] = {
	{'N', 0.0, -1.0, 0.66, 0.0},
	{'S', 0.0, 1.0, -0.66, 0.0},
	{'E', 1.0, 0.0, 0.0, 0.66},
	{'W', -1.0, 0.0, 0.0, -0.66},
	};

	return (orient);
}

/**
 * @brief Initializes the player's position and orientation.
 *
 * Sets the player's position to the center of the map cell (y, x) and assigns
 * the direction and camera plane vectors according to the player's orientation
 * character ('N', 'S', 'E', 'W').
 *
 * Uses the get_orientation() lookup table to find the correct direction vectors.
 * If the character is invalid, an error message is printed.
 *
 * @param game Pointer to the game struct containing the player and map.
 * @param y Row index of the player in the map grid.
 * @param x Column index of the player in the map grid.
 */
static void	set_player_position(t_game *game, int y, int x)
{
	int					i;
	char				c;
	const t_orientation	*orient;

	c = game->map.grid[y][x];
	game->player.pos_x = x + TILE_CENTER_OFFSET;
	game->player.pos_y = y + TILE_CENTER_OFFSET;
	orient = get_orientation();
	i = 0;
	while (i < 4)
	{
		if (orient[i].c == c)
		{
			game->player.dir_x = orient[i].dir_x;
			game->player.dir_y = orient[i].dir_y;
			game->player.plane_x = orient[i].plane_x;
			game->player.plane_y = orient[i].plane_y;
			return ;
		}
		i++;
	}
	print_errors(PLAYER_ORIENTATION, NULL, NULL);
}

/**
 * @brief Sets the player position if a player character is found at the
 * given coordinates.
 *
 * Checks if the map cell at (y, x) contains a player character
 * ('N', 'S', 'E', 'W'). If a player is already found, prints an error for
 * multiple players. Otherwise, sets the player's position and orientation
 * in the game struct and replaces the map cell with '0' to mark it as empty.
 *
 * @param game Pointer to the game structure containing the map and player.
 * @param player_found Pointer to an integer flag indicating whether a player
 *        has been found.
 * @param y Row index in the map grid.
 * @param x Column index in the map grid.
 * @return EXIT_SUCCESS if the player was successfully set or no player at
 *         this cell.
 * @return EXIT_FAILURE if multiple players are detected.
 */
static int	set_player(t_game *game, int *player_found, int y, int x)
{
	if (is_player(game->map.grid[y][x]))
	{
		if (*player_found)
		{
			print_errors(PLAYER_MULTI, NULL, NULL);
			return (EXIT_FAILURE);
		}
		*player_found = 1;
		set_player_position(game, y, x);
		game->map.grid[y][x] = '0';
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief Initialize the player in the map.
 *
 * Iterates through the map grid to find the player's starting position
 * (one of 'N', 'S', 'E', 'W'). Validates that exactly one player exists,
 * sets the player's coordinates and orientation, and replaces the map
 * tile with '0' to mark it as empty space.
 *
 * @param game Pointer to the game structure containing the map.
 * @return EXIT_SUCCESS if the player was successfully initialized,
 *         EXIT_FAILURE if multiple players are found or no player exists.
 */
int	init_player(t_game *game)
{
	int	x;
	int	y;
	int	player_found;

	player_found = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (set_player(game, &player_found, y, x) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	if (!player_found)
	{
		print_errors(PLAYER_NONE, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
