/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:52:52 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 13:53:01 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* file validation errors */
# define ARG_USAGE "Usage: ./cub3D <valid_map.cub>"
# define FILENAME_NULL "Filename is NULL, please use a valid file"
# define FILENAME_LENGHT "Filename is too short. Minimum required: x.cub"
# define FILENAME_EXTENSION "Filename extension is invalid. Expected: .cub"
# define FILENAME_HIDDEN "Filename can't be a hidden file"

/* player parsing errors */
# define PLAYER_ORIENTATION "Invalid player orientation"
# define PLAYER_NONE "Player not found"
# define PLAYER_MULTI "Multiple players detected"

/* map parsing errors */
# define MAP_DIMENSIONS "Invalid map dimensions"
# define MAP_TOO_LARGE "Map too large (max 100 x 100)"
# define MAP_CHAR "Invalid character in map"
# define MAP_ZERO_BORDER "Map not closed: 0 on border"
# define MAP_ZERO_INVALID "Map not closed: 0 adjacent to invalid cell"
# define MAP_SPACE "Map not closed: space adjacent to walkable area"
# define MAP_LOAD "Failed to load map grid"

/* header parsing errors */
# define HEADER_DUPLICATE "Duplicate header identifier"
# define HEADER_MISSING "Missing headers. Expected: 6"
# define HEADER_TOO_MANY "Too many headers. Expected: 6"

/* texture-related errors */
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
# define TEXTURE_LOAD "Failed to load texture"
# define TEXTURE_DIMENSION "Texture is not 64x64"
# define TEXTURE_DATA "Failed to retrieved necessary textures data"

/* map and header constants */
# define PLAYER "NSEW"
# define TILE_CENTER_OFFSET 0.5
# define MAX_MAP_W 100
# define MAX_MAP_H 100
# define RGB_SIZE 3
# define TEX_SIZE 4

/* table constants */
# define ADJACENT_DIR_COUNT 4
# define PLAYER_ORIENT_COUNT 4
# define FOV_PLANE 0.66

/* game elements */
# define WINDOWS_X 1920
# define WINDOWS_Y 1080
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define WINDOWS_MSG "Welcome to CUB3D"
# define MIN_WALL_DISTANCE 0.001
# define VERTICAL_WALL 0
# define HORIZONTAL_WALL 1
# define TEXTURE_FALLBACK_COLOR 0x000000
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define MOUSE_SENSITIVITY 0.00005

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
	char	**grid;
	int		width;
	int		height;
	int		floor_color[RGB_SIZE];
	int		ceiling_color[RGB_SIZE];
	char	*tex_paths[TEX_SIZE];
	bool	id_set[HEADER_SIZE];
	int		map_start_line;
}	t_map;

/* tracks which keys are currently pressed */
typedef struct s_keys
{
	bool	w_pressed;
	bool	a_pressed;
	bool	s_pressed;
	bool	d_pressed;
	bool	left_arrow_pressed;
	bool	right_arrow_pressed;
}	t_keys;

/* represents the player's state in the game */
typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

/* texture data loaded from .xpm files */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

/* encapsulates the entire game state and resources */
typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
	t_texture	textures[4];
	t_player	player;
	t_map		map;
	t_keys		keys;
	int			last_mouse_x;
	int			last_mouse_y;
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
	int		keycode;
	void	(*action)(t_game *);
	bool	*flag_ptr;
}	t_key_binding;

/* ray structure for raycasting calculation */
typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_ray;

/* ray result structure containing all raycasting outputs */
typedef struct s_ray_result
{
	double	wall_dist;
	int		wall_dir;
	double	wall_x;
}	t_ray_result;

/* column drawing parameters for rendering */
typedef struct s_col
{
	int	x;
	int	start;
	int	end;
	int	color;
}	t_col;

/* drawing info for a complete column (ceiling + wall + floor) */
typedef struct s_draw_info
{
	int		x;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		ceiling;
	int		floor;
	int		wall_dir;
	double	wall_x;
}	t_draw_info;

/* =========================== */
/*           EVENTS            */
/* =========================== */

/* events handlers.c */
int						handle_keypress(int keycode, void *param);
int						handle_keyrelease(int keycode, void *param);
int						handle_close(void *param);
int						game_loop(void *param);
t_key_binding			*get_key_bindings(t_game *game);

/* mouse_handler.c */
int						handle_mouse_move(int x, int y, void *param);
void					apply_camera_rotation(t_game *game, double angle);

/* hooks.c */
void					setup_hooks(t_game *game);

/* player_actions_rotate.c */
void					rotate_left(t_game *game);
void					rotate_right(t_game *game);

/* player_actions_move.c */
void					move_forward(t_game *game);
void					move_backward(t_game *game);
void					strafe_left(t_game *game);
void					strafe_right(t_game *game);

/* =========================== */
/*           INIT              */
/* =========================== */

/* init_data.c */
void					init_t_game(t_game *game);

/* init_mlx.c */
int						init_graphics(t_game *game);

/* init_textures.c */
int						init_textures(t_game *game);

/* =========================== */
/*         PARSING             */
/* =========================== */

/* check_headers.c */
int						check_header_count(const char *path);

/* file_validations.c */
int						validate_argument(char *filename);

/* header_table.c */
const t_header_entry	*get_header_entry(const char *line);

/* header_utils.c */
void					next_line(char **line, int fd, int *i);
bool					line_is_empty(char *line);

/* parse_and_validate_cub */
int						parse_and_validate_cub(char *path, t_game *game);

/* parse_header.c */
int						parse_header(const char *path, t_map *map);

/* parse_header_line.c */
int						parse_header_line(t_map *map, char *line);

/*parse_map.c */
int						parse_map(const char *path, t_map *map);

/*parse_map_utils.c */
int						max_int(int a, int b);
int						open_cub_file(const char *path);
void					print_map_grid(t_map *map);
void					free_map_grid(t_map *map);
void					free_partial_grid(t_map *map, int filled_rows);

/* parse_rgb.c */
int						parse_rgb(const char *value, int rgb_values[RGB_SIZE]);

/* player_setup.c */
int						init_player(t_game *game);

/* player_setup_utils.c */
void					print_player_info(t_player *player);

/* validate_map.c */
int						check_valid_map(t_map *map);

/* =========================== */
/*           RENDERS           */
/* =========================== */

/* draw_pixels.c*/
void					draw_pixel_in_buffer(t_game *game, int x, int y,
							int color);

/* =========================== */
/*         RAYCAST             */
/* =========================== */

/* dda.c */
t_ray_result			cast_ray(t_game *game, double ray_dir_x,
							double ray_dir_y);

/* dda_utils.c */
bool					check_hit(t_game *game, t_ray *ray);
double					calculate_wall_x(t_ray *ray, double pos_x, double pos_y,
							double wall_dist);
int						get_wall_direction(t_ray *ray);

/* raycast_utils.c */
int						calculate_tex_x(double wall_x);
int						get_texture_pixel(t_texture *texture, int tex_x,
							int tex_y);
void					draw_textured_wall_slice(t_game *game,
							t_draw_info info);

/* raycast.c */
void					render_frame(t_game *game);

/* =========================== */
/*           UTILS             */
/* =========================== */

/* ascii art */
void					print_ascii_art_hello(void);

/* cleanup_exit.c */
void					cleanup_textures(t_game *game);
void					free_t_map(t_map *map);
void					cleanup_exit(t_game *game);

/* print_errors.c */
void					print_errors(char *p1, char *p2, char *p3);

/* rgb_tab_to_int.c */
int						rgb_tab_to_int(int rgb[RGB_SIZE]);

#endif
