/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:55:41 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 11:43:49 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../libft/libft.h"
# include "/home/jwhitley/.local/mlx/mlx.h" 
//# include <mlx.h>
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
# define ESC 65307

# define WINX 1200
# define WINY 720

# define PI M_PI 

# define ERROR_1 "Calloc: Data Struct\n"
# define ERROR_2 "Calloc: Map Struct\n"
# define ERROR_3 "Couldn't open mapfile\n"
# define ERROR_4 "Calloc: Map Array\n"
# define ERROR_5 "Strdup: Map Array\n"
# define ERROR_6 "Calloc: Texture Struct\n"
# define ERROR_7 "Calloc: Ray Struct\n"
# define ERROR_8 "Calloc: Game Struct\n"
# define ERROR_9 "Multiple Definitions of a texture in mapfile (see above)\n"
# define ERROR_10 "Couldnt open texture file (see above)\n"
# define ERROR_11 "Multiple Definitions of color in mapfile\n"
# define ERROR_12 "Invalid color value in mapfile\n"
# define ERROR_13 "Invalid data in mapfile (see above)\n"
# define ERROR_14 "Required textures/colors not found in mapfile\n"
# define ERROR_15 "No map found / map data not at end of mapfile\n"
# define ERROR_16 "No player start position found\n"
# define ERROR_17 "More than one player start position found\n"
# define ERROR_18 "Calloc: Map Validation: map_copy array\n"
# define ERROR_19 "Calloc: Map Validation: checked / cell array\n"
# define ERROR_20 "Map not surrounded by walls\n"
# define ERROR_21 "Invalid mapfile: .cub file required"

typedef struct s_data	t_data;

typedef struct s_cell
{
	int		y;
	int		x;
	int		ny;
	int		nx;
	int		dy[4];
	int		dx[4];
	int		i;
	char	**m_cp;
	bool	**checked;
}	t_cell;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
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
	double	dRay;
	double	ra;
	float	xo;
	float	yo;
	t_data	*data;
}	t_ray;

typedef struct s_player
{
	float		p_x;
	float		p_y;
	float		p_dx;
	float		p_dy;
	float		p_ang;
	t_data		*data;
}	t_player;

typedef struct s_map
{
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

/* init_structs.c */

void	init_game_struct(t_data *data);
void	init_ray_struct(t_data *data);
void	init_texture_struct(t_data *data);
void	init_player_struct(t_data *data);
void	init_map_struct(t_data *data, char *map_file);

/* parsing.c */
void	parsing_error(t_data *data, char *msg, char *line);
void	parsing(t_data *data, t_map *map);

/* parsing_utils.c */
bool	is_junk_line(char *line);
int		rgb_color_conversion(void *mlx, int r, int g, int b);
bool	open_mapfile(t_map *map);
void	close_mapfile(t_map *map);

/* get_textures.c */
void	get_textures(t_map *map, t_tex *tex, int *map_start);

/* get_map.c */
void	get_map(t_map *map, int *total_lines);

/* validate_map.c */
void	validate_map(t_map *map);

/* validate_map_walls.c */
void	validate_map_walls(t_map *map, char **map_copy);

/* set_player_data */
void	set_player_data(t_data *data, t_map *map);

/* error_exit.c */
void	free_array(char **array);
void	exit_game(t_data *data, bool error, char *msg);

/* free_structs.c */
void	free_game_struct(t_data *data);
void	free_tex_struct(t_data *data);
void	free_map_struct(t_data *data);

/* images_bg_game.c */
void	set_walls(t_data *data, t_game *game, int x);
void	get_game_img_data(t_data *data, t_game *game);
void	set_image_data(t_data *data);

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
