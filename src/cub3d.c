#include "../inc/cub3d.h"

void	destroy_free(t_data *data)
{
	mlx_destroy_window(data->init, data->win);
	mlx_destroy_display(data->init);
	free(data->init);
	free(data->map);
	free(data);
}

t_data	*init_structs(void)	
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	data->init = mlx_init();
	data->win = mlx_new_window(data->init, 1280, 720, "TEST GAME");
	data->map = ft_calloc(1, sizeof(t_map));
	return (data);
}

int	main(void)
{
	t_data	*data;

	data = init_structs();
	draw_map(data);
	destroy_free(data);
	return (0);
}
