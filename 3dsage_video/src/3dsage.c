#include "../inc/3dsage.h"
#include "mlx.h"

t_data	*init_data_struct(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	if (!data)
		exit_game(data, ERROR_1);
	data->init = mlx_init();
	data->win = mlx_new_window(data->init, 1024, 512, "3dsage Test");
	data->bg = mlx_new_image(data->init, 1024, 512);
	data->player = mlx_new_image(data->init, 10, 10);	
	return (data);
}

int	main(void)
{
	t_data	*data = init_data_struct();
	set_image_data(data);
	//run_game(data);
	mlx_put_image_to_window(data->init, data->win, data->bg, 0, 0);
	sleep(5);
	exit_game(data, NULL);
}
