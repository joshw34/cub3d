#include "../../inc/test.h"
void	parsing(t_data *data, t_map *map)
{
	int line_n;

	line_n = 0;
	if (!open_mapfile(map))
		exit_game(data, true, ERROR_3);
	get_textures(map, data->tex, &line_n);
	get_map(map, line_n);
	close_mapfile(map);
	db_print_tex_info(data->tex);
}
