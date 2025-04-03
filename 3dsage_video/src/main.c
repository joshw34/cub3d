#include "../inc/test.h"

void	init_ray_struct(t_data *data)
{
	data->ray = ft_calloc(1, sizeof(t_ray));
	if (!data->ray)
		exit_game(data, true, ERROR_7);
	data->ray->data = data;
}

void	init_texture_struct(t_data *data)
{
	data->textures = ft_calloc(1, sizeof(t_textures));
	if (!data->textures)
		exit_game(data, true, ERROR_6);
}

void	init_player_struct(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->player->p_x = 100.0;
	data->player->p_y = 100.0;
	data->player->data = data;
}

void	init_map_struct(t_data *data, char *map_file)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		exit_game(data, true, ERROR_2);
	data->map->map_file = map_file;
	data->map->lines = 0;
	data->map->len = -1;
	data->map->data = data;
}

t_data	*init_structs(char	*map_file)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		exit_game(data, true, ERROR_1);
	init_map_struct(data, map_file);
	init_player_struct(data);
	init_texture_struct(data);
	init_ray_struct(data);
	return (data);
}

/* Data split in to multiple structs to keep tidy, may need to reorganise later */
int	main(int ac, char **av)
{
	printf("%f\n", PI);
	t_data	*data;
	if (ac != 2)
		exit(EXIT_FAILURE);
	data = init_structs(av[1]);
	parse_map(data);
	run_game(data);
	exit_game(data, false, NULL);
}
