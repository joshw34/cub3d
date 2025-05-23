/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_bg_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:47:57 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/21 18:58:35 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* called from raycasting loop for each vertical line
   line_h = length of vertical line to draw
   starty = offset to centre of window
   direction used to set different colors for horizontal/vertical line */
void	set_walls(t_data *data, t_game *game, int x)
{
	int		*pixel;

	game->line_h = (64 * WINY) / data->ray->d_ray;
	if (game->line_h > WINY)
		game->line_h = WINY;
	game->start_y = (WINY / 2) - (game->line_h / 2);
	game->end_y = game->start_y + game->line_h;
	game->start_y_first_value = game->start_y;
	while (game->start_y < game->end_y)
	{
		pixel = (int *)(game->game_addr + (game->start_y * data->ln_len + x
					* (data->bpp / 8)));
		if (game->direction == 'v')
			*pixel = get_texel_value(data);
		else if (game->direction == 'h')
			*pixel = get_texel_value(data);
		game->start_y++;
	}
}

/* get game_img data here so we can memcpy bg_addr->game_addr later.
   This is done last so the bpp, ln_len and endian vars in data struct are
   set to the correct values for the game image */
void	get_game_img_data(t_data *data, t_game *game)
{
	game->game_addr = mlx_get_data_addr(game->game_img, &data->bpp,
			&data->ln_len, &data->endian);
	game->total_bytes = data->ln_len * WINY;
}

/* Static background image. Is not actually put on screen, it is memcpy ->the
   game image before adding the walls. This means that the game image doesn't
   have to be cleared for each new frame */
static	void	set_background_img(t_data *data, int x, int y)
{
	int		*pixel;

	data->game->bg_addr = mlx_get_data_addr(data->game->bg_img, &data->bpp,
			&data->ln_len, &data->endian);
	while (y < WINY)
	{
		while (x < WINX)
		{
			pixel = (int *)(data->game->bg_addr + (y * data->ln_len + x
						* (data->bpp / 8)));
			if (y <= (WINY / 2))
				*pixel = data->tex->c;
			else
				*pixel = data->tex->f;
			x++;
		}
		x = 0;
		y++;
	}
	get_game_img_data(data, data->game);
}

/* Set image buffer data for all static images. set_walls() is called from the
   raycasting function. As all images share the same bpp, ln_len and endian
   variables, background needs to be last here */
void	set_image_data(t_data *data)
{
	set_background_img(data, 0, 0);
}
