/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:33:53 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 13:36:39 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Initialise all images then redraw in loop after every keypress */
void init_map(t_data *data, t_game *game) {
  mlx_put_image_to_window(data->init, data->rc_win, game->game_img, 0, 0);
}

/* Create mlx, window and image pointers. */
static void init_mlx_data(t_data *data) {
  data->rc_win = mlx_new_window(data->init, WINX, WINY, "cub3d");
  data->game->bg_img = mlx_new_image(data->init, WINX, WINY);
  data->game->game_img = mlx_new_image(data->init, WINX, WINY);
}

void run_game(t_data *data) {
  init_game_struct(data);
  init_ray_struct(data);
  init_mlx_data(data);
  set_image_data(data);
  raycasting(data, data->ray, data->player, data->game);
  init_map(data, data->game);
  mlx_hook(data->rc_win, DestroyNotify, 0, &win_close, data);
  mlx_expose_hook(data->rc_win, &expose_win, data);
  mlx_hook(data->rc_win, KeyPress, KeyPressMask, &key, data);
  mlx_loop(data->init);
}
