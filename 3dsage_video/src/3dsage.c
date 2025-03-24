#include "../inc/3dsage.h"

t_data	*init_data_struct(void)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	if (!data)
		exit_game(data, true, ERROR_1);
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
	run_game(data);
	exit_game(data, false, NULL);
}
