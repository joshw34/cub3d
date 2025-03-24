#ifndef SAGE_H
#define SAGE_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
void	exit_game(t_data *data, char *msg);

/* set_color.c */
void	set_image_data(t_data *data);
#endif
