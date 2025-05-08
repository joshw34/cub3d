NAME = test 

SRC_DIR = ./src
PARSING_SRC_DIR = ./src/parsing
EXIT_FREE_SRC_DIR = ./src/exit_free
GAME_SRC_DIR = ./src/game

INC_DIR = ./inc
LIBFT_DIR = ./libft
MLX_DIR = /home/jwhitley/.local/mlx

LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -lXext -lX11

SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/debug_funcs.c \
			$(PARSING_SRC_DIR)/parsing.c \
			$(PARSING_SRC_DIR)/get_textures.c \
			$(PARSING_SRC_DIR)/get_map.c \
			$(EXIT_FREE_SRC_DIR)/error_exit.c \
			$(GAME_SRC_DIR)/image_bg_game.c \
			$(GAME_SRC_DIR)/images_map.c \
			$(GAME_SRC_DIR)/run_game.c \
			$(GAME_SRC_DIR)/game_hooks.c \
			$(GAME_SRC_DIR)/raycasting.c \
			$(GAME_SRC_DIR)/raycasting_utils.c \
			$(GAME_SRC_DIR)/raycasting_utils_2.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

REMOVE = rm -f
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wno-unused-result -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@echo "$(NAME): Linking"
	@$(CC) $(OBJ_FILES) $(LIBFT) $(LIBMLX) $(MLX_FLAGS) -lm -o $(NAME)
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
