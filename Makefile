#     ██████╗██╗   ██╗██████╗ ██████╗ ██████╗
#    ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
#    ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
#    ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
#    ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
#     ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝

# === general configuration ===
NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -MMD -MP
SYSTEM_FLAGS = -lXext -lX11 -lm
RM = rm -f

# === directories ===
SRC_DIR = src
OBJ_DIR = obj
MLX_DIR = minilibx-linux
LIBFT_DIR = libft

# === librairies ===
MLX_A = $(MLX_DIR)/libmlx.a
LIBFT_A = $(LIBFT_DIR)/libft.a

# === includes ===
INC_DIR = -Iincludes -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# === source files ===
SRC =	src/main.c \
		src/events/events_handler.c \
		src/events/game_loop.c \
		src/events/hooks.c \
		src/events/mouse_handler.c \
		src/events/player_actions_move.c \
		src/events/player_actions_rotate.c \
		src/init/init_data.c \
		src/init/init_mlx.c \
		src/init/init_textures.c \
		src/parsing/check_headers.c \
		src/parsing/file_validations.c \
		src/parsing/header_table.c \
		src/parsing/header_utils.c \
		src/parsing/parse_and_validate_cub.c \
		src/parsing/parse_rgb.c \
		src/parsing/parse_header.c \
		src/parsing/parse_header_line.c \
		src/parsing/parse_map.c \
		src/parsing/parse_map_utils.c \
		src/render/draw_pixels.c \
		src/raycast/dda.c \
		src/raycast/dda_utils.c \
		src/raycast/raycast_utils.c \
		src/raycast/raycast.c \
		src/parsing/player_setup.c \
		src/parsing/player_setup_utils.c \
		src/parsing/validate_map.c \
		src/utils/ascii_art.c \
		src/utils/cleanup_exit.c \
		src/utils/print_errors.c \
		src/utils/rgb_tab_to_int.c \

# object files preserving subdirectory structure
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS = $(OBJ:.o=.d)

# === build rules ===
all: $(NAME)

# build cub3d executable
$(NAME) : $(MLX_A) $(LIBFT_A) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(MLX_A) $(SYSTEM_FLAGS) $(LIBFT_A)

# rule for object compilation into obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# === cleaning ===
clean:
	$(RM) $(OBJ) $(DEPS)
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# === dependencies ===
-include $(DEPS)

.PHONY: all clean fclean re test
