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

# define ARG_USAGE "Usage: ./cub3D <valid_map.cub>"
# define NULL_FILENAME "filename is NULL, please use a valid file"
# define LENGTH_FILENAME "filename is too short. Minimum required: x.cub"
# define EXTENSION_FILENAME "filename extension is invalid. Expected: .cub"
# define HIDDEN_FILENAME "filename can't be a hidden file"

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

/* point of this struct */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* point of this struct */
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
	int			img_endian; 	// endian format of the image (from mlx_get_data_addr)
	// === Assets ===
	// t_tex	   textures[4]; // array of 4 loaded textures (NO, SO, WE, EA)
	// === Game state ===
	t_player	player;		// player data (position, direction, camera plane)
	t_map		map;			// map data (grid, size, textures paths, colors)
}	t_game;

/* =========================== */
/*         PARSING             */
/* =========================== */

/* parsing/file_validations.c */
int			validate_argument(char *filename);

/* utils/print_errors.c */
void		print_errors(char *p1, char *p2, char *p3);

#endif
