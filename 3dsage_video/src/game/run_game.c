#include "../../inc/test.h"

/* Initialise all images then redraw in loop after every keypress */
void	init_map(t_data *data)
{
	//mlx_put_image_to_window(data->init, data->map_win, data->map->m_img, 0, 0);
	//mlx_put_image_to_window(data->init, data->map_win, data->player->p_img, data->player->p_x, data->player->p_y);
	//db_draw_line(data, data->player);
	mlx_put_image_to_window(data->init, data->rc_win, data->game->game_img, 0, 0);
	//mlx_put_image_to_window(data->init, data->rc_win, data->map->m_img, 10, 10);
}

/* Create mlx, window and image pointers.
 * Map window to be removed later and map image put on game window.
   Player start angle set here for now, will be taken from mapfile during parsing */
static void	init_mlx_data(t_data *data, t_player *player, t_map *map)
{
	(void)map;
	//data->map_win = mlx_new_window(data->init, map->size_x, map->size_y, "minimap");
	data->rc_win = mlx_new_window(data->init, WINX, WINY, "cub3d");
	data->game->bg_img = mlx_new_image(data->init, WINX, WINY);
	data->game->game_img = mlx_new_image(data->init, WINX, WINY);
	//data->map->m_img = mlx_new_image(data->init, map->size_x, map->size_y);
	//data->player->p_img = mlx_new_image(data->init, 10, 10);
	//data->ray->y_hit_img = mlx_new_image(data->init, 10, 10);
	data->player->p_ang =  PI;
	data->player->p_dx = cos(player->p_ang) * 5;
	data->player->p_dy = sin(player->p_ang) * 5;
}

void	run_game(t_data *data)
{
	init_mlx_data(data, data->player, data->map);
	set_image_data(data);
	raycasting(data, data->ray, data->player, data->game);
	init_map(data);
	//mlx_hook(data->map_win, DestroyNotify, 0, &win_close, data);
	mlx_hook(data->rc_win, DestroyNotify, 0, &win_close, data);
	//mlx_expose_hook(data->map_win, &expose_win, data);
	mlx_expose_hook(data->rc_win, &expose_win, data);
	mlx_hook(data->rc_win, KeyPress, KeyPressMask, &key, data);
	mlx_loop(data->init);
}
