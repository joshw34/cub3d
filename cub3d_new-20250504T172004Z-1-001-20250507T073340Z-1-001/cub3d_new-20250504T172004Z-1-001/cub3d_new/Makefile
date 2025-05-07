

SRC_DIR = ./src
INC_DIR = ./inc

SRC_FILES =	$(SRC_DIR)/cub3d.c \
			$(SRC_DIR)/draw_functions.c \
			$(SRC_DIR)/draw_functions_2.c \
			$(SRC_DIR)/game_initialization.c \
			$(SRC_DIR)/utils.c  




CC				:= cc
CFLAGS			:=  -g -fsanitize=address
MLX_FLAGS		:= -Lmlx -lmlx -lX11 -lXext -Ofast -lm -I./mlx
NAME			:= cub3d
MLX				:= mlx/libmlx.a
#GNL				:= gnl/get_next_line.a
OBJS			:= $(SRC_FILES:.c=.o)

all: $(MLX) $(NAME)

$(MLX):
	git clone https://github.com/42Paris/minilibx-linux.git mlx
	$(MAKE) -C mlx

#$(GNL):
#	$(MAKE) -C gnl

$(NAME): $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
clean:
	rm -rf $(OBJS)
fclean:		clean
	rm -rf	$(NAME)

re:			fclean all

.PHONY:	all clean fclean re