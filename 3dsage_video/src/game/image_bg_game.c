#include "../../inc/test.h"

/* called from raycasting loop for each vertical line
   lineH = length of vertical line to draw
   startx ->endx = width of vertical line 
   starty = offset to centre of window
   direction used to set different colors for horizontal/vertical line. can be removed for textures */
void	set_walls(t_data *data, t_game *game, int x)
{
	int		*pixel;

	game->lineH = (64 * WINY) / data->ray->dRay;
	if (game->lineH > WINY)
		game->lineH = WINY;
	game->start_x = data->ray->r * (WINX / 60);
	game->end_x = game->start_x + (WINX / 60);
	game->start_y = (WINY / 2) - (game->lineH / 2);
	game->end_y = game->start_y + game->lineH;
	x = game->start_x;
	while (game->start_y < game->end_y)
	{
		while (x < game->end_x)
		{
			pixel = (int *)(game->game_addr + (game->start_y * data->ln_len
				+ x * (data->bpp / 8)));
			if (game->direction == 'v')
				*pixel = rgb_color_conversion(data->init, 255, 0, 0);
			else if (game->direction == 'h')
				*pixel = rgb_color_conversion(data->init, 200, 0, 0);
			x++;
		}
		x = game->start_x;
		game->start_y++;
	}
}

/* get game_img data here so we can memcpy bg_addr->game_addr later. This is done last so the
   bpp, ln_len and endian vars in data struct are set to the correct values for the game image */
static	void	get_game_img_data(t_data *data, t_game *game)
{
	game->game_addr = mlx_get_data_addr(game->game_img, &data->bpp,
		&data->ln_len, &data->endian);
	game->total_bytes = data->ln_len * WINY;
}

/* Static background image. Blue/green currently set manually but will take the colors supplied
   in the mapfile.  Is not actually put on screen, it is memcpy ->the game image before adding the
   walls. This means that the game image doesn't have to be cleared for each new frame */
static	void	set_background_img(t_data *data, int x, int y, int color)
{
	int		*pixel;
	(void)color;

	data->game->bg_addr = mlx_get_data_addr(data->game->bg_img, &data->bpp,
		&data->ln_len, &data->endian);
	while (y < WINY)
	{
		while (x < WINX)
		{
			pixel = (int *)(data->game->bg_addr + (y * data->ln_len + x *
				(data->bpp / 8)));
			if (y <= (WINY / 2))
				*pixel = rgb_color_conversion(data->init, 37, 29, 235);
			else
				*pixel = rgb_color_conversion(data->init, 28, 144, 14);
			x++;
		}
		x = 0;
		y++;
	}
	get_game_img_data(data, data->game);
}

/* Set image buffer data for all static images. set_walls() is called from the raycasting function
   As all images share the same bpp, ln_len and endian variables, background needs to be last here
*/
void	set_image_data(t_data *data)
{
	set_player_img(data, 0, 0);
	set_map_img(data);
	set_background_img(data, 0, 0, BLACK);
}
