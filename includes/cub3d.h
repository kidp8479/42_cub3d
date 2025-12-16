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
# include <stdbool.h>

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
# define MAP_TOO_LARGE "Map too large (max 500 x 500)"
# define MAP_CHAR "Invalid character in map"
# define MAP_ZERO_BORDER "Map not closed: 0 on border"
# define MAP_ZERO_INVALID "Map not closed: 0 adjacent to invalid cell"
# define MAP_SPACE "Map not closed: space adjacent to walkable area"
# define LOAD_MAP "Failed to load map grid"
# define NULL_TGAME "Invalid t_game structure pointer"
# define MLX_INIT "Initialization of the MLX connection failed"
# define WIN_INIT "Initialization of the MLX windows failed"
# define IMG_INIT "Initialization of the MLX image buffer failed"
# define IMG_DATA "Retrieving IMG data failed"

/* map constants */
# define PLAYER "NSEW"
# define TILE_CENTER_OFFSET 0.5
# define MAX_MAP_W 500
# define MAX_MAP_H 500

/* game elements */
# define WINDOWS_X 800
# define WINDOWS_Y 600
# define WINDOWS_MSG "Welcome to CUB3D"
// movement speed constant (units per frame)
// smaller = slower, larger = faster
# define MOVE_SPEED 0.05

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

/* Tracks which keys are currently pressed */
typedef struct s_keys
{
	bool	w_pressed;
	bool	a_pressed;
	bool	s_pressed;
	bool	d_pressed;
	bool	left_arrow_pressed;
	bool	right_arrow_pressed;
}	t_keys;

/* Represents the player's state in the game */
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
	t_keys		keys;		// tracks which keys are currently pressed
		// === Mouse ===
	int			last_mouse_x;	// last mouse X position for delta calculation
	int			last_mouse_y;	// last mouse Y position for delta calculation
}	t_game;

/* Player orientation struct for the look up table */
typedef struct s_orientation
{
	char	c;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_orientation;

/* Key binding struct for mapping keys to actions */
typedef struct s_key_binding
{
	int		keycode; // X11 keycode for this specific key (ex: XK_w, XK_Left)
	void	(*action)(t_game *); // function pointer to the action that should be executed
	bool	*flag_ptr;  // Pointer to the boolean flag that represents whether this key is currently pressed (true) or released (false)
}	t_key_binding;

/* Ray structure for raycasting calculation */
typedef struct s_ray
{
	double	dir_x;			// X component of ray direction
	double	dir_y;			// Y component of ray direction
	int		map_x;			// Current grid X coordinate
	int		map_y;			// Current grid Y coordinate
	double	side_dist_x;	// Distance ray travels to next X grid line
	double	side_dist_y;	// Distance ray travels to next Y grid line
	double	delta_dist_x;	// Distance between X grid lines along ray
	double	delta_dist_y;	// Distance between Y grid lines along ray
	int		step_x;			// Step direction in X (either +1 or -1)
	int		step_y;			// Step direction in Y (either +1 or -1)
	int		side;			// Was wall hit on X-side (0) or Y-side (1)?
}	t_ray;

/* =========================== */
/*           EVENT             */
/* =========================== */

/* cleanup_exit.c */
void			cleanup_exit(t_game *game);

/* events handlers.c */
int				handle_keypress(int keycode, void *param);
int				handle_keyrelease(int keycode, void *param);
int				handle_close(void *param);
int				game_loop(void *param);
t_key_binding	*get_key_bindings(t_game *game);

/* mouse_handler.c */
int				handle_mouse_move(int x, int y, void *param);

/* hooks.c */
void			setup_hooks(t_game *game);

/* player_actions_rotate.c */
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

/* player_actions_move.c */
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			strafe_left(t_game *game);
void			strafe_right(t_game *game);

/* =========================== */
/*           INIT              */
/* =========================== */

/* init_data.c */
void			init_data(t_game *game);
int				load_and_validate_map(char *path, t_game *game);

/* init_mlx.c */
int				init_game_data(t_game *game);

/* =========================== */
/*         PARSING             */
/* =========================== */

/* file_validations.c */
int				validate_argument(char *filename);

/*parse_map.c */
int				parse_map(const char *path, t_map *map);

/*parse_map_utils.c */
int				open_cub_file(const char *path);
void			print_map_grid(t_map *map);
void			free_map(t_map *map);
void			free_partial_grid(t_map *map, int filled_rows);
void			free_map_copy(char **grid, int map_height);

/* player_setup_utils.c */
void			print_player_info(t_player *player);

/* player_setup.c */
int				init_player(t_game *game);

/* validate_map.c */
int				check_valid_map(t_map *map);

/* =========================== */
/*           RENDERS           */
/* =========================== */

/* draw_pixels.c*/
void			draw_pixel_in_buffer(t_game *game, int x, int y, int color);

/* =========================== */
/*         RAYCASTING          */
/* =========================== */

/* dda.c */
double			cast_ray(t_game *game, double ray_dir_x, double ray_dir_y);

/* simple_ray.c */
void			render_single_ray(t_game *game);

/* raycast.c */
void			render_frame(t_game *game);

/* =========================== */
/*           UTILS             */
/* =========================== */

/* ascii art */
void			print_ascii_art_hello(void);

/* utils/print_errors.c */
void			print_errors(char *p1, char *p2, char *p3);

#endif
