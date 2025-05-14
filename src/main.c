#include "../inc/cub3d.h"

t_data	*init_structs(char	*map_file)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_game(data, true, ERROR_1);
	data->init = mlx_init();
	init_map_struct(data, map_file);
	init_player_struct(data);
	init_texture_struct(data);
	init_ray_struct(data);
	init_game_struct(data);
	return (data);
}

/* Data split in to multiple structs to keep tidy, need to reorganise later */
int	main(int ac, char **av)
{
	t_data	*data;
	if (ac != 2)
		exit(EXIT_FAILURE);
	data = init_structs(av[1]);
	parsing(data, data->map);
	run_game(data);
	exit_game(data, false, NULL);
}
