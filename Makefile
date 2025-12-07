#     ██████╗██╗   ██╗██████╗ ██████╗ ██████╗
#    ██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗
#    ██║     ██║   ██║██████╔╝ █████╔╝██║  ██║
#    ██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║
#    ╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝
#     ╚═════╝ ╚═════╝ ╚═════╝ ╚ ╚═════╝

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
		src/init/init_data.c \
		src/parsing/file_validations.c \
		src/parsing/parse_map.c \
		src/parsing/parse_map_utils.c \
		src/parsing/player_setup.c \
		src/parsing/player_setup_utils.c \
		src/utils/print_errors.c \

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
