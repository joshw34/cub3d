#include "../../inc/test.h"

void	init_map(t_data *data)
{
	//mlx_put_image_to_window(data->init, data->win, data->bg, 0, 0);
	mlx_put_image_to_window(data->init, data->win, data->map->m_img, 0, 0);
	mlx_put_image_to_window(data->init, data->win, data->player->p_img, data->player->p_x, data->player->p_y);
}

static void	init_mlx(t_data *data)
{
	data->init = mlx_init();
	data->win = mlx_new_window(data->init, data->map->size_x, data->map->size_y, "Test");
	data->bg = mlx_new_image(data->init, data->map->size_x, data->map->size_y);
	data->map->m_img = mlx_new_image(data->init, data->map->size_x, data->map->size_y);
	data->player->p_img = mlx_new_image(data->init, 10, 10);
}

void	run_game(t_data *data)
{
	init_mlx(data);
	set_image_data(data);
	init_map(data);
	mlx_hook(data->win, DestroyNotify, 0, &win_close, data);
	mlx_expose_hook(data->win, &expose_win, data);
	mlx_do_key_autorepeaton(data->init);
	mlx_key_hook(data->win, &key, data);
	mlx_loop(data->init);
}
