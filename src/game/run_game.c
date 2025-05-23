/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:33:53 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/22 16:10:07 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
static	void	set_map2(t_data *data, int x, int y, int color)
{
	int		*pixel;
	char	*addr;
	int		size_x;
	int		size_y;
	int		start_x;
	
	start_x = x;
	size_x = x + 64 - 1;
	size_y = y + 64 - 1;
	addr = mlx_get_data_addr(data->map->m_img, &data->bpp, &data->ln_len,
			&data->endian);
	while (y < size_y)
	{
		while (x < size_x)
		{
			pixel = (int *)(addr + (y * data->ln_len + x * (data->bpp / 8)));
			*pixel = color;
			x++;
		}
		x = start_x;
		y++;
	}
}

/* Cycle through map array, send x + y pixel for top-left corner of each tile
   Currently sets each tile as 64x64 pixels, needs to be smaller and dynamically assigned */
void	set_map_img(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = data->map->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				set_map2(data, j * 64, i * 64, rgb_color_conversion(data->init, 255,255,255));
			else if (map[i][j] == '1' || map[i][j] == ' ')
				set_map2(data, j * 64, i * 64, rgb_color_conversion(data->init, 0, 255, 0));
			j++;
		}
		i++;
	}
}

/* Red square for player location. Currently set to 10x10 pixel. Actual player location is
   top-left corner of square */
void	set_player_img(t_data *data, int x, int y)
{
	char	*addr;
	int		*pixel;

	addr = mlx_get_data_addr(data->player->p_img, &data->bpp, &data->ln_len,
			&data->endian);
	while (y < 10)
	{
		while (x < 10)
		{
			pixel = (int *)(addr + (y * data->ln_len + x * (data->bpp / 8)));
			*pixel = rgb_color_conversion(data->init, 255, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
}


/* Initialise all images then redraw in loop after every keypress */
void	init_map(t_data *data, t_game *game)
{
	mlx_put_image_to_window(data->init, data->map_win, data->map->m_img, 0, 0);
	mlx_put_image_to_window(data->init, data->map_win, data->player->p_img, data->player->p_x, data->player->p_y);
	db_draw_line(data, data->player);
	mlx_put_image_to_window(data->init, data->rc_win,
		game->game_img, 0, 0);

}

/* Create mlx, window and image pointers. */
static void	init_mlx_data(t_data *data)
{
	data->map_win = mlx_new_window(data->init, data->map->len * 64, data->map->lines * 64, "minimap");
	data->rc_win = mlx_new_window(data->init, WINX, WINY, "cub3d");
	data->player->p_img = mlx_new_image(data->init, 10, 10);
	data->ray->y_hit_img = mlx_new_image(data->init, 10, 10);
	data->game->bg_img = mlx_new_image(data->init, WINX, WINY);
	data->game->game_img = mlx_new_image(data->init, WINX, WINY);
	data->map->m_img = mlx_new_image(data->init, data->map->len * 64, data->map->lines * 64);
	set_player_img(data, 0, 0);
	set_map_img(data);
}

void	run_game(t_data *data)
{
	init_ray_struct(data);
	init_game_struct(data);
	init_mlx_data(data);
	set_image_data(data);
	raycasting(data, data->ray, data->player, data->game);
	init_map(data, data->game);
	mlx_hook(data->rc_win, DestroyNotify, 0, &win_close, data);
	mlx_expose_hook(data->rc_win, &expose_win, data);
	mlx_hook(data->rc_win, KeyPress, KeyPressMask, &key, data);
	mlx_loop(data->init);
}
