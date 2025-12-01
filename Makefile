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
SYSTEM_FLAGS = -lnext -lX11 -lm
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
SRCS =	main.c \

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

# === cleaning ===
clean:
	$(RM) $(OBJS) $(DEPS)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean:
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# === dependencies ===
-include $(DEPS)

.PHONY: all clean fclean re
