#include "../../inc/test.h"

bool	is_junk_line(char	*line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
			i++;
	if (line[i] != '1')
		return (true);
	return (false);
}

int	rgb_color_conversion(void *mlx, int r, int g, int b)
{
	int color;
	int	mlx_color;

	color = (r << 16) | (g << 8) | b;
	mlx_color = mlx_get_color_value(mlx, color);
	return (mlx_color);
}

bool	open_mapfile(t_map *map)
{
	map->fd = open(map->map_file, O_RDONLY);
	if (map->fd == -1)
		return (false);
	return (true);
}

void	close_mapfile(t_map *map)
{
	close(map->fd);
	map->fd = -1;
}

void	parsing(t_data *data, t_map *map)
{
	int total_lines;
	int	map_lines;

	total_lines = 0;
	map_lines = 0;
	if (!open_mapfile(map))
		exit_game(data, true, ERROR_3);
	get_textures(map, data->tex, &total_lines);
	get_map(map, &total_lines);
	//VALIDATE MAP
}
