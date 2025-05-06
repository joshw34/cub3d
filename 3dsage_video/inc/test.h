#ifndef TEST_H
# define TEST_H

# include "../libft/libft.h"
//# include "/home/jwhitley/.local/mlx/mlx.h" 
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>

# define W 119
# define A 97
# define S 115
# define D 100

# define LT 65361
# define RT 65363

# define WINX 1200 
# define WINY 600

# define BLACK 0x000000
# define WHITE 0xffffff
# define GREEN 0x008000
# define RED 0xb92537

# define PI M_PI 

# define ERROR_1 "Calloc: Data Struct\n"
# define ERROR_2 "Calloc: Map Struct\n"
# define ERROR_3 "Couldn't open mapfile\n"
# define ERROR_4 "Calloc: Map Array\n"
# define ERROR_5 "Strdup: Map Array\n"
# define ERROR_6 "Calloc: Texture Struct\n"
# define ERROR_7 "Calloc: Ray Struct\n"
# define ERROR_8 "Calloc: Game Struct\n"
# define ERROR_9 "Multiple Definitions of a texture in mapfile\n"
# define ERROR_10 "Couldnt open texture file\n"
# define ERROR_11 "Multiple Definitions of color in mapfile\n"
# define ERROR_12 "Invalid color value in mapfile\n"
# define ERROR_13 "Required textures/colors not found in mapfile\n"

typedef struct  s_data t_data;

typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F;
	int		C;
	t_data	*data;
}	t_tex;

typedef struct s_game
{
	void	*bg_img;
	char	*bg_addr;
	void	*game_img;
	char	*game_addr;
	int		total_bytes;
	int		lineH;
	int		start_x;
	int		end_x;
	int		start_y;
	int		end_y;
	char	direction;
	t_data	*data;
}	t_game;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		dof;
	float	rx;
	float	ry;
	float	v_rx;
	float	h_rx;
	float	v_ry;
	float	h_ry;
	float	dH;
	float	dV;
	float	dRay;
	float	ra;
	float	xo;
	float	yo;
	void	*y_hit_img;
	t_data	*data;
}	t_ray;

typedef struct s_player
{
	void		*p_img;
	float		p_x;
	float		p_y;
	float		p_dx;
	float		p_dy;
	float		p_ang;
	t_data		*data;
}	t_player;

typedef struct s_map
{
	void	*m_img;
	char	**map;
	char	*map_file;
	int		fd;
	int		lines;
	int		len;
	int		size_x;
	int		size_y;
	t_data	*data;
}	t_map;

typedef struct s_data
{
	void		*init;
	void		*map_win;
	void		*rc_win;
	t_map		*map;
	t_player	*player;
	t_tex		*tex;
	t_ray		*ray;
	t_game		*game;
	int			bpp;
	int			ln_len;
	int			endian;
}	t_data;

/* parsing.c */
void	parsing(t_data *data, t_map *map);

/* get_textures.c */
void	get_textures(t_map *map, t_tex *tex, int *map_start);

/* get_map.c */
void	get_map(t_map *map, int line_n);

/* parsing_utils.c */
int		rgb_color_conversion(void *mlx, int r, int g, int b);
bool	open_mapfile(t_map *map);
void	close_mapfile(t_map *map);
int		ft_strlen_no_nl(const char *str);

/* error_exit.c */
void	free_array(char **array);
void	exit_game(t_data *data, bool error, char *msg);

/* images_bg_game.c */
void	set_walls(t_data *data, t_game *game, int x);
void	set_image_data(t_data *data);

/* images_map.c */
void	set_player_img(t_data *data, int x, int y);
void	set_map_img(t_data *data);
void	fix_fisheye(t_ray *ray, t_player *player);

/* run_game.c */
void	init_map(t_data *data);
void	run_game(t_data *data);

/* game_hooks.c */
int		key(int keysym, t_data *data);
int		expose_win(t_data *data);
int		win_close(t_data *data);

/* raycasting.c */
void	raycasting(t_data *data, t_ray *ray, t_player *player, t_game *game);

/* raycasting_utils.c */
float	ray_len(t_ray *ray, t_player *play);
void	found_wall(t_ray *ray, t_player *play, char direction);
void	map_pixel_to_array(t_ray *ray);
float	deg_to_rad(int deg);
void	reset_ray_data(t_ray *ray);

/* raycasting_utils_2.c */
void	set_next_angle(t_ray *ray);
void	fix_fisheye(t_ray *ray, t_player *player);
void	find_closest_hit(t_ray *ray, t_game *game);

/* debug_funcs.c */
void	db_show_first_hit(t_data *data);
void	db_show_both_hits(t_data *data);
void	db_print_player_x_y(t_player *player);
void	db_draw_line(t_data *data, t_player *play);
void	db_print_pdx_pdy(t_player *p);
void	db_err_print(char *str);
void	db_print_map_info(t_data *data, bool add_spaces);
void	db_print_tex_info(t_tex *tex);

#endif
