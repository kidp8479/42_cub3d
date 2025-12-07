CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

INC_DIR = -I../includes -I../libft/includes -I../minilibx-linux

# Directories
SRC_DIR = ../src
UNIT_DIR = unit
BIN_DIR = bin
LIB_DIR = lib
OBJ_DIR = obj
LIBFT_DIR = ../libft
MLX_DIR = ../minilibx-linux

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX    = $(MLX_DIR)/libmlx.a
LIBCUB = $(LIB_DIR)/libcub3d.a

# project source files (excluding main.c)
SRC = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c))

# build object files from sorce files
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# unit tests
UNIT_TESTS = $(wildcard $(UNIT_DIR)/test_*.c)
UNIT_BIN = $(UNIT_TESTS:$(UNIT_DIR)/%.c=$(BIN_DIR)/%)

# Default target: build and run all tests
all: $(LIBCUB) $(UNIT_BIN)
	@echo "\nRunning all tests..."
	@for test in $(UNIT_BIN); do \
		./$$test || echo "FAILED $$test"; \
	done

#build static library
$(LIBCUB): $(OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $(OBJ)

# compile sorce files into LIB_DIR
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

# Build each test binary
$(BIN_DIR)/%: $(UNIT_DIR)/%.c $(LIBCUB) $(LIBFT) $(MLX)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $< $(LIBCUB) $(LIBFT) $(MLX) \
		-lm -lXext -lX11 -o $@

# Build dependent libraries
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

# Clean test binaries
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(LIB_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# cleans 3rd party dependency (MLX)
deepclean: fclean
	$(MAKE) -C $(MLX_DIR) clean

# Build a single test
# Usage: make run TEST=unit/test_name.c
run: $(BIN_DIR)/$(notdir $(TEST))
	./$(BIN_DIR)/$(notdir $(TEST))

$(BIN_DIR)/$(notdir $(TEST)): $(TEST) $(LIBCUB) $(LIBFT) $(MLX)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(INC_DIR) $(TEST) $(LIBCUB) $(LIBFT) $(MLX) \
		-lm -lXext -lX11 -o $@
