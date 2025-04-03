#include "../../inc/test.h"

/* Initialse all images then redraw in loop */
void	init_map(t_data *data)
{
	//mlx_put_image_to_window(data->init, data->win, data->bg, 0, 0);
	mlx_put_image_to_window(data->init, data->win, data->map->m_img, 0, 0);
	mlx_put_image_to_window(data->init, data->win, data->player->p_img, data->player->p_x, data->player->p_y);
	db_draw_line(data, data->player);
}

/* Create mlx, window and image pointers*/
/* Player start angle set here for now */
static void	init_mlx_data(t_data *data, t_player *player, t_map *map)
{
	data->init = mlx_init();
	data->win = mlx_new_window(data->init, map->size_x, map->size_y, "cub3d");
	data->bg = mlx_new_image(data->init, map->size_x, map->size_y);
	data->map->m_img = mlx_new_image(data->init, map->size_x, map->size_y);
	data->player->p_img = mlx_new_image(data->init, 10, 10);
	data->ray->y_hit_img = mlx_new_image(data->init, 10, 10);
	data->player->p_ang =  PI * 2;
	fprintf(stderr, "%f\n", data->player->p_ang);
	data->player->p_dx = cos(player->p_ang) * 5;
	fprintf(stderr, "x = %f\n", data->player->p_dx);
	data->player->p_dy = sin(player->p_ang) * 5;
	fprintf(stderr, "y = %f\n", data->player->p_dy);
	printf("Initial Position:\n");
	//db_print_player_coord(player);
}

void	run_game(t_data *data)
{
	init_mlx_data(data, data->player, data->map);
	set_image_data(data);
	printf("#######################################################################################################################\n");
	init_map(data);
	//raycasting(data);
	//db_show_both_hits(data);
	mlx_hook(data->win, DestroyNotify, 0, &win_close, data);
	mlx_expose_hook(data->win, &expose_win, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, &key, data);
	mlx_loop(data->init);
}
