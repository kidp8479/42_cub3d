#ifndef CUB3D_H
# define CUB3D_H

/* =========================== */
/*          INCLUDES           */
/* =========================== */

# include "libft.h"
# include <mlx.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>

/* =========================== */
/*         DEFINE              */
/* =========================== */

/* error messages */
# define ARG_USAGE "Usage: ./cub3D <valid_map.cub>"
# define NULL_FILENAME "Filename is NULL, please use a valid file"
# define LENGTH_FILENAME "Filename is too short. Minimum required: x.cub"
# define EXTENSION_FILENAME "Filename extension is invalid. Expected: .cub"
# define HIDDEN_FILENAME "Filename can't be a hidden file"
# define MAP_DIMENSIONS "Invalid map dimensions"
# define LOAD_MAP "Failed to load map grid"
# define NULL_TGAME "Invalid t_game structure pointer"
# define MLX_INIT "Initialization of the MLX connection failed"
# define WIN_INIT "Initialization of the MLX windows failed"
# define IMG_INIT "Initialization of the MLX image buffer failed"
# define IMG_DATA "Retrieving IMG data failed"

/* map constants */
# define PLAYER "NSEW"
# define TILE_CENTER_OFFSET 0.5

/* game elements */
# define WINDOWS_X 800
# define WINDOWS_Y 600
# define WINDOWS_MSG "Welcome to cub3D"

/* =========================== */
/*        STRUCTURES           */
/* =========================== */

/* map structure - stores parsed .cub file data */
typedef struct s_map
{
	char	**grid;			// 2d array of chars that represents the map layout
							// ex: '1' = wall, '0' = empty space, 'N' = player, etc.
	int		width;			// width of the map (max number of columns)
							// useful for checking map boundaries
	int		height;			// height of the map (number of lines)
							// used to loop over the map safely
	char	*no_path;		// file path for north wall texture (from .cub file)
	char	*so_path;		// file path for south wall texture
	char	*we_path;		// file path for west wall texture
	char	*ea_path;		// file path for east wall texture
	int		floor_color;	// rgb color for the floor, converted to int (0xRRGGBB)
	int		ceiling_color;	// rgb color for the ceiling, converted to int (0xRRGGBB)
}	t_map;

/* Represents the player’s state in the game */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* Encapsulates the entire game state and resources */
typedef struct s_game
{
	// === MLX ===
	void		*mlx;		// pointer to the MLX connection (init with mlx_init)
	void		*win;		// pointer to the window (created with mlx_new_window)
	// === Image buffer ===
	void		*img;		// pointer to an image used for drawing pixels
	char		*img_addr;	// memory address of the image pixels (from mlx_get_data_addr)
	int			img_bpp;		// bits per pixel (from mlx_get_data_addr)
	int			img_line_len;	// number of bytes in a line of the image (from mlx_get_data_addr)
	int			img_endian;	// endian format of the image (from mlx_get_data_addr)
	// === Assets ===
	// t_tex	   textures[4]; // array of 4 loaded textures (NO, SO, WE, EA)
	// === Game state ===
	t_player	player;		// player data (position, direction, camera plane)
	t_map		map;			// map data (grid, size, textures paths, colors)
}	t_game;

/* player orientation struct for the look up table */
typedef struct s_orientation
{
	char	c;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_orientation;

/* =========================== */
/*           INIT              */
/* =========================== */

/* init_data.c */
void	init_data(t_game *game);
int		load_and_validate_map(char *path, t_game *game);

/* init_mlx.c */
int		init_game_data(t_game *game);

/* =========================== */
/*         PARSING             */
/* =========================== */

/* file_validations.c */
int		validate_argument(char *filename);

/*parse_map.c */
int		parse_map(const char *path, t_map *map);

/*parse_map_utils.c */
int		open_cub_file(const char *path);
void	print_map_grid(t_map *map);
void	free_map(t_map *map);
void	free_partial_grid(t_map *map, int filled_rows);
void	free_map_copy(char **grid, int map_height);

/* player_setup_utils.c */
void	print_player_info(t_player *player);

/* player_setup.c */
int		init_player(t_game *game);

/* validate_map.c */
int		check_valid_map(t_map *map, t_player *player);

/* =========================== */
/*           RENDERS           */
/* =========================== */

/* draw_pixels.c*/
void	draw_pixel_in_buffer(t_game *game, int x, int y, int color);

/* =========================== */
/*           UTILS             */
/* =========================== */

/* utils/print_errors.c */
void	print_errors(char *p1, char *p2, char *p3);

#endif
