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

/* File validation errors */
# define ARG_USAGE "Usage: ./cub3D <valid_map.cub>"
# define NULL_FILENAME "Filename is NULL, please use a valid file"
# define LENGTH_FILENAME "Filename is too short. Minimum required: x.cub"
# define EXTENSION_FILENAME "Filename extension is invalid. Expected: .cub"
# define HIDDEN_FILENAME "Filename can't be a hidden file"

/* player parsing errors */
# define PLAYER_ORIENTATION "Invalid player orientation"
# define PLAYER_NONE "Player not found"
# define PLAYER_MULTI "Multiple players detected"

/* map parsing errors */
# define MAP_DIMENSIONS "Invalid map dimensions"
# define MAP_TOO_LARGE "Map too large (max 500 x 500)"
# define MAP_CHAR "Invalid character in map"
# define MAP_ZERO_BORDER "Map not closed: 0 on border"
# define MAP_ZERO_INVALID "Map not closed: 0 adjacent to invalid cell"
# define MAP_SPACE "Map not closed: space adjacent to walkable area"
# define MAP_LOAD "Failed to load map grid"

/* header parsing errors */
# define HEADER_DUPLICATE "Duplicate header identifier"
# define HEADER_MISSING "Missing headers. Expected: 6"
# define HEADER_TOO_MANY "Too many headers. Expected: 6"

/* Texture-related errors */
# define TEXTURE_TRIM_FAIL "Texture path trim failed"
# define TEXTURE_INVALID "Texture file invalid or cannot be opened"
# define TEXTURE_DUPLICATE "Duplicate texture identifier"
# define TEXTURE_EMPTY "Texture path missing or empty"

/* RGB/color related errors */
# define RGB_SPLIT_FAIL "RGB: split failed"
# define RGB_INVALID_FORMAT "RGB: exactly 3 components ranged 0-255 required"
# define RGB_TOO_MANY "RGB: Too many values. Expected: 3"

/* MLX errors */
# define NULL_TGAME "Invalid t_game structure pointer"
# define MLX_INIT "Initialization of the MLX connection failed"
# define WIN_INIT "Initialization of the MLX windows failed"
# define IMG_INIT "Initialization of the MLX image buffer failed"
# define IMG_DATA "Retrieving IMG data failed"

/* map and header constants */
# define PLAYER "NSEW"
# define TILE_CENTER_OFFSET 0.5
# define MAX_MAP_W 500
# define MAX_MAP_H 500
# define RGB_SIZE 3
# define TEX_SIZE 4

/* game elements */
# define WINDOWS_X 800
# define WINDOWS_Y 600
# define WINDOWS_MSG "Welcome to CUB3D"

/* =========================== */
/*        STRUCTURES           */
/* =========================== */

typedef enum e_header_type
{
	ID_NONE = -1,
	ID_NO = 0,
	ID_SO = 1,
	ID_WE = 2,
	ID_EA = 3,
	ID_FLOOR = 4,
	ID_CEILING = 5,
	HEADER_SIZE = 6
}	t_header_type;

/* map structure - stores parsed .cub file data */
typedef struct s_map
{
	char	**grid;			// 2d char array representing map layout
	int		width;			// map width (max number of columns)
	int		height;			// map height (number of lines)
	int		floor_color[RGB_SIZE];
	int		ceiling_color[RGB_SIZE];
	char	*tex_paths[TEX_SIZE];
	bool	id_set[HEADER_SIZE];
	int		map_start_line; //where map lines start
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

/* player orientation struct for the look up table */
typedef struct s_orientation
{
	char	c;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_orientation;

/* header lines look up table */
typedef struct e_header_entry
{
	const char		*key;
	t_header_type	id;
	size_t			len;
}	t_header_entry;

/* key binding struct for mapping keys to actions */
typedef struct s_key_binding
{
	int		keycode; // X11 keycode for this specific key (ex: XK_w, XK_Left)
	void	(*action)(t_game *); // function pointer to the action that should be executed
	bool	*flag_ptr;  // Pointer to the boolean flag that represents whether this key is currently pressed (true) or released (false)
}	t_key_binding;

/* =========================== */
/*           EVENTS            */
/* =========================== */

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

/* check_headers.c */
int				check_header_count(const char *path);

/* file_validations.c */
int				validate_argument(char *filename);

/* header_table.c */
const t_header_entry	*get_header_entry(const char *line);

/* header_utils.c */
void			next_line(char **line, int fd, int *i);
bool			line_is_empty(char *line);

/* parse_header.c */
int				parse_header(const char *path, t_map *map);

/* parse_header_line.c */
int				parse_header_line(t_map *map, char *line);

/*parse_map.c */
int				parse_map(const char *path, t_map *map);

/*parse_map_utils.c */
int				max_int(int a, int b);
int				open_cub_file(const char *path);
void			print_map_grid(t_map *map);
void			free_map_grid(t_map *map);
void			free_partial_grid(t_map *map, int filled_rows);

/* parse_rgb.c */
int				parse_rgb(const char *value, int rgb_values[RGB_SIZE]);

/* player_setup.c */
int				init_player(t_game *game);

/* player_setup_utils.c */
void			print_player_info(t_player *player);

/* validate_map.c */
int				check_valid_map(t_map *map);

/* =========================== */
/*           RENDERS           */
/* =========================== */

/* draw_pixels.c*/
void			draw_pixel_in_buffer(t_game *game, int x, int y, int color);

/* =========================== */
/*           UTILS             */
/* =========================== */

/* ascii art */
void			print_ascii_art_hello(void);

/* cleanup_exit.c */
void			free_t_map(t_map *map);
void			cleanup_exit(t_game *game);

/* utils/print_errors.c */
void			print_errors(char *p1, char *p2, char *p3);

#endif
