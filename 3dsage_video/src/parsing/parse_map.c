#include "../../inc/test.h"

/* No error checking yet, only map is parsed, no textures/colors */

/* Parse map using gnl, remove \n if present */
static	bool	get_map_array(t_map *map)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	line = get_next_line(map->fd);
	while (line)
	{
		map->map[i] = ft_strdup(line);
		if (!map->map[i])
			return (false);
		len = ft_strlen(map->map[i]);
		if (map->map[i][len - 1] == '\n')
			map->map[i][len - 1] = '\0';
		free(line);
		line = get_next_line(map->fd);
		i++;
	}
	map->map[i] = NULL;
	if (line)
		free(line);
	return (true);
}

/* Allocate 2d array to hold map, return error if failed */
static	bool	allocate_map_array(t_map *map)
{
	map->map = ft_calloc(map->lines + 1, sizeof(char *));
	if (!map->map)
		return (false);
	return (true);
}

/* Calculate number of lines and length of longest line, calculate size of minimap.
   Minimap cells set to 64x64, this needs to be scaled down */
static	bool	get_line_data(t_map *map)
{
	char	*line;
	int		line_len;

	if (open_mapfile(map) == false)
		return (false);
	line = get_next_line(map->fd);
	while (line)
	{
		map->lines++;
		line_len = ft_strlen_no_nl(line);
		if (line_len > map->len)
			map->len = line_len;
		free(line);
		line = get_next_line(map->fd);
	}
	if (line)
		free(line);
	close(map->fd);
	map->size_x = map->len * 64;
	map->size_y = map->lines * 64;
	return (true);
}

void	parse_map(t_data *data)
{
	if (get_line_data(data->map) == false)
		exit_game(data, true, ERROR_3);
	if (allocate_map_array(data->map) == false)
		exit_game(data, true, ERROR_4);
	if (open_mapfile(data->map) == false)
		exit_game(data, true, ERROR_3);
	if (get_map_array(data->map) == false)
		exit_game(data, true, ERROR_5);
	db_print_map_info(data, true);
}
