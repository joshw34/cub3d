#ifndef SAGE_H
#define SAGE_H

# include "../libft/libft.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define ERROR_1 "Calloc Error: Data Struct\n"

typedef struct	s_data
{
	void	*init;
	void	*win;
	void    *bg;
	void	*player;
    int     bpp;
    int     line_length;
    int     endian;
} t_data;

/* error_exit.c */
void	exit_game(t_data *data, bool error, char *msg);

/* set_color.c */
void	set_image_data(t_data *data);

/* run_game.c */
void	init_map(t_data *data);
void	run_game(t_data *data);

/* game_hooks.c */
int	key(int keysym, t_data *data);
int	expose_win(t_data *data);
int	win_close(t_data *data);

#endif
