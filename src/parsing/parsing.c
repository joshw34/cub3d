#include "../../inc/test.h"

void	parsing_error(t_data *data, char *msg, char *line)
{
	if (line)
	{
		printf("Line: %s\n", line);
		free(line);
	}
	line = get_next_line(data->map->fd);
	while (line)
	{
		free(line);
		line = get_next_line(data->map->fd);
	}
	exit_game(data, true, msg);
}

static	void	check_extension(t_map *map)
{
	char	*file;
	int		l;

	file = map->map_file;
	l = ft_strlen(file) - 1;
	if (file[l] != 'b' || file[l - 1] != 'u' || file[l - 2] != 'c'
		|| file[l - 3] != '.')
		exit_game(map->data, true, ERROR_21);
}

void	parsing(t_data *data, t_map *map)
{
	int total_lines;

	total_lines = 0;
	check_extension(map);
	if (!open_mapfile(map))
		exit_game(data, true, ERROR_3);
	get_textures(map, data->tex, &total_lines);
	get_map(map, &total_lines);
	validate_map(map);
	set_player_data(data, map);
}
