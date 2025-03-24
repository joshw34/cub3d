#include "../inc/3dsage.h"
#include "mlx.h"

void	init_map(t_data *data)
{
	mlx_put_image_to_window(data->init, data->win, data->bg, 0, 0);
}

void	run_game(t_data *data)
{
	init_map(data);
	mlx_hook(data->win, DestroyNotify, 0, &win_close, data);
	mlx_expose_hook(data->win, &expose_win, data);
	mlx_key_hook(data->win, &key, data);
	mlx_loop(data->init);
}
