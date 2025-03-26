#ifndef TEST_H
# define TEST_H

# include "../libft/libft.h"
# include "/home/jwhitley/.local/mlx/mlx.h" 
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define W 119
# define A 97
# define S 115
# define D 100

# define UP 65362
# define LT 65361
# define DN 65364
# define RT 65363

# define MAPX 1024 
# define MAPY 512

# define ERROR_1 "Calloc Error: Data Struct\n"
# define ERROR_2 "Calloc Error: Map Struct\n"
# define ERROR_3 "Couldn't open mapfile\n"
# define ERROR_4 "Calloc Error: Map Array\n"
# define ERROR_5 "Strdup Error: Map Array\n"

typedef struct s_map
{
	char	**map;
	char	*map_file;
	int		fd;
	int		lines;
	int		len;
}	t_map;

typedef struct s_data
{
	void	*init;
	void	*win;
	t_map	*map;	
	void	*bg;
	void	*player;
	int		bpp;
	int		ln_len;
	int		endian;
	int		p_x;
	int		p_y;
}	t_data;

/* parse_map.c */
void	parse_map(t_data *data);

/* error_exit.c */
void	exit_game(t_data *data, bool error, char *msg);

/* set_color.c */
void	set_image_data(t_data *data);

/* run_game.c */
void	init_map(t_data *data);
void	run_game(t_data *data);

/* game_hooks.c */
int		key(int keysym, t_data *data);
int		expose_win(t_data *data);
int		win_close(t_data *data);

/* utils.c */
bool	open_mapfile(t_map *map);
int		ft_strlen_no_nl(const char *str);

/* debug_funcs.c */
void	db_print_map_info(t_data *data, bool add_spaces);

#endif
