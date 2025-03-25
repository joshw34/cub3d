#include "../inc/3dsage.h"

t_data	*init_data_struct(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_game(data, true, ERROR_1);
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		exit_game(data, true, ERROR_2);
	data->init = mlx_init();
	data->win = mlx_new_window(data->init, MAPX, MAPY, "3dsage Test");
	data->bg = mlx_new_image(data->init, MAPX, MAPY);
	data->player = mlx_new_image(data->init, 10, 10);
	data->p_x = 95;
	data->p_y = 95;
	return (data);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		exit(EXIT_FAILURE);
	t_data	*data = init_data_struct();
	parse_map(data, av[1]);
	set_image_data(data);
	run_game(data);
	exit_game(data, false, NULL);
}
