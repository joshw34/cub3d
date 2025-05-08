#include "../inc/test.h"

/* Everything needed to draw the final 3d image */
void	init_game_struct(t_data *data)
{
	data->game = ft_calloc(1, sizeof(t_game));
	if (!data->game)
		exit_game(data, true, ERROR_8);
	data->game->data = data;
}

/* All variables necessary for raycasting. */
void	init_ray_struct(t_data *data)
{
	data->ray = ft_calloc(1, sizeof(t_ray));
	if (!data->ray)
		exit_game(data, true, ERROR_7);
	data->ray->data = data;
}

/* texture files to be taken from mapfile. floor / ceiling colours may go here */
void	init_texture_struct(t_data *data)
{
	data->tex = ft_calloc(1, sizeof(t_tex));
	if (!data->tex)
		exit_game(data, true, ERROR_6);
	data->tex->data = data;
	data->tex->F = -1;
	data->tex->C = -1;
}

/* Player position set manually, needs to taken from mapfile */
void	init_player_struct(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->player->p_x = 550.0;
	data->player->p_y = 416.0;
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
