#include "../inc/test.h"

void	init_map_struct(t_data *data, char *map_file)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		exit_game(data, true, ERROR_2);
	data->map->map_file = map_file;
	data->map->lines = 0;
	data->map->len = -1;
}

t_data	*init_data_struct(char	*map_file)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_game(data, true, ERROR_1);
	data->init = mlx_init();
	//data->win = mlx_new_window(data->init, MAPX, MAPY, "3dsage Test");
	//data->bg = mlx_new_image(data->init, MAPX, MAPY);
	data->player = mlx_new_image(data->init, 10, 10);
	data->p_x = 95;
	data->p_y = 95;
	init_map_struct(data, map_file);
	return (data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		exit(EXIT_FAILURE);
	data = init_data_struct(av[1]);
	parse_map(data);
	set_image_data(data);
	//run_game(data);
	exit_game(data, false, NULL);
}
