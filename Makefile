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
MLX_DIR = minilibx-linux
LIBFT_DIR = libft

# === librairies ===
MLX_A = $(MLX_DIR)/libmlx.a
LIBFT_A = $(LIBFT_DIR)/libft.a

# === includes ===
INC_DIR = -Iincludes -I$(LIBFT_DIR)/includes -I$(MLX_DIR)

# === sources ===
SRCS =	src/main.c \
		src/init/init_data.c \
		src/parsing/file_validations.c \
		src/parsing/parse_map.c \
		src/parsing/parse_map_utils.c \
		src/utils/print_errors.c \

OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

# === build rules ===
all: $(NAME)

$(NAME) : $(MLX_A) $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX_A) $(SYSTEM_FLAGS) $(LIBFT_A)

%.o: %.c
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

# === testing === (quick set up, this probably can be more efficient later)
TEST_NAME = unit_tests

TEST_SRCS =	tests/unit/test_file_validation.c \
			tests/unit/test_init_mlx.c \
			src/parsing/file_validations.c \
			src/parsing/parse_map.c \
			src/parsing/parse_map_utils.c \
			src/utils/print_errors.c \

TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_DEPS = $(TEST_SRCS:.c=.d)

test: $(MLX_A) $(LIBFT_A) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -o $(TEST_NAME) $(MLX_A) $(SYSTEM_FLAGS) $(LIBFT_A)
	./$(TEST_NAME)
	$(RM) $(TEST_NAME) $(TEST_OBJS) $(TEST_DEPS)

# === cleaning ===
clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# === dependencies ===
-include $(DEPS)

.PHONY: all clean fclean re test
