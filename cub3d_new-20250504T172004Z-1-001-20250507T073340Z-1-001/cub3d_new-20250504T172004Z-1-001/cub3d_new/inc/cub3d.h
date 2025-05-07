/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:29:42 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/07 12:12:01 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx_int.h"
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# ifndef PI
#  define PI 3.1415926535
# endif

# ifndef RED
#  define RED 0xffff0000
# endif

# ifndef GREEN
 //# define GREEN 16711680
 #define GREEN 0xFF33FF34
# endif

# ifndef FOV
#  define FOV 60
# endif

# ifndef BLUE
# define BLUE 0xff3364ff
//#  define BLUE 65280
# endif
typedef struct s_box
{
    void *game;

}   t_box;

typedef struct s_player
{
    void    *game;
    float    x;
    float    y;
    float   dx;
    float   dy;
    float    angle;

}   t_player;

typedef struct s_map
{
    int x_max;
    int y_max;
    int *map;
}   t_map;
typedef struct s_ray
{
    float  sum_of_dx;
    float  sum_of_dy;
    int    wall_x;
    int    wall_y;
    float  angle;
    float  distance;
}   t_ray;

typedef struct s_game
{
	void	*mlx;
	void	*window;
    void	*window_3d;
    void	*img;
    void    *img_3d;
    void    *data;
    int     length;
    int     width;
    int     *pixel_array;
    int     *pixel_array_3d;
    int     bpp;
    int     size_line;
    int     endian;
    t_ray   **fov;
    t_map     map;
    t_box   *box;
    t_player    player;

}				t_game;

 //game_initialization.c
 void   init_game(t_game *game);
 void   put_pixel(t_game *game, int x, int y, long long int color);
 int    execute_keyboard_command(int key_code, void *game);
 //utils.c
 int    is_drawable(int x, int y, t_game *game);
 //int    is_a_wall(int x, int y, t_game *game);
  int    is_a_wall(int x, int y, t_game *game, t_ray *ray);
 void free_fov(t_ray **fov);
 //draw_function.c
 void   draw_circle(t_game *game, int rayon, int xo, int yo, long long int color);
 void   draw_circle_2(t_game *game);
 void   *ft_memset(void *s, int c, size_t n);
 void   draw_map(t_game *game);
 //draw_function_2.c
 void   draw_full_block(t_game *game, int x, int y);
 void   draw_edge_block(t_game *game, int x, int y);
 void draw_fov(t_game *game, float angle, long long int color);
 //void draw_ray(t_game *game, float angle, long long int color, t_ray **ray);
 void draw_ray(t_game *game, float angle, long long int color, t_ray *ray);
  //void draw_ray(t_game *game, float angle, long long int color);

#endif

