#include "../inc/3dsage.h"
#include "fcntl.h"

void	get_line_data(t_map *map, char *map_file)
{
	char	*line;

	map->fd = open(map_file, O_RDONLY);
	map->lines = 0;
	map->len = -1;
	line = get_next_line(map->fd);
	while (line)
	{
		map->lines++;
		if ((int)ft_strlen(line) > map->len)
			map->len = (int)ft_strlen(line);
		free(line);
		line = get_next_line(map->fd);
	}
	if (line)
		free(line);
}

void	parse_map(t_data *data, char *map_file)
{
	get_line_data(data->map, map_file);
	ft_printf("Lines = %d\nLen = %d\n", data->map->lines, data->map->len);
}
