/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:27:53 by jwhitley          #+#    #+#             */
/*   Updated: 2024/08/28 16:53:09 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../libft/functions/get_next_line/get_next_line.h"
#include "../libft/libft.h"
#include "./minilibx/mlx.h"
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define W 119
#define A 97
#define S 115
#define D 100

#define UP 65362
#define LT 65361
#define DN 65364
#define RT 65363

#define ESC 65307

/*typedef struct s_m_data {
  int rows;
  int cols;
  int p_row;
  int p_col;
  int e_row;
  int e_col;
  int c;
  int e;
  int p;
  int moves;
} t_m_data;*/

typedef struct  s_map
{
  int x_low;
  int x_high;
  int y_low;
  int y_high;
  int x;
  int y;
} t_map;

typedef struct s_data
{
  void  *init;
  void  *win;
  t_map *map;
} t_data;

/* draw_map.c */
void  draw_map(t_data *data);

#endif
