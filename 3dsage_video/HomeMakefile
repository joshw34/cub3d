NAME = test 

SRC_DIR = ./src
INC_DIR = ./inc
LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -lmlx -lXext -lX11

SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/parse_map.c \
			$(SRC_DIR)/error_exit.c \
			$(SRC_DIR)/image_buffers.c \
			$(SRC_DIR)/run_game.c \
			$(SRC_DIR)/game_hooks.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/debug_funcs.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

REMOVE = rm -f
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wno-unused-result -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@echo "$(NAME): Linking"
	@$(CC) $(OBJ_FILES) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME): Ready"

$(LIBFT):
	@echo "Libft: Compiling"
	@make -s all -C $(LIBFT_DIR)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -s clean -C $(LIBFT_DIR)
	@$(REMOVE) $(OBJ_FILES)
	@echo "so_long: Object Files Removed"

fclean:
	@make -s fclean -C $(LIBFT_DIR)
	@$(REMOVE) $(OBJ_FILES)
	@echo "so_long: Object Files Removed"
	@$(REMOVE) $(NAME)
	@echo "so_long: Executable Removed"

re: fclean all

.PHONY: all clean fclean re
