#include "../../inc/test.h"
void	parsing(t_data *data, t_map *map)
{
	int line_n;

	line_n = 0;
	if (!open_mapfile(map))
		exit_game(data, true, ERROR_3);
	get_textures(map, data->tex, &line_n);
	//get_map(map, line_n);
	map->map = ft_calloc(11, sizeof(char *));
	map->map[0] = ft_strdup("1111111111");
	map->map[1] = ft_strdup("1000000001");
	map->map[2] = ft_strdup("1001001001");
	map->map[3] = ft_strdup("1000001001");
	map->map[4] = ft_strdup("1000001001");
	map->map[5] = ft_strdup("1000010001");
	map->map[6] = ft_strdup("1000100001");
	map->map[7] = ft_strdup("1010000001");
	map->map[8] = ft_strdup("1000000001");
	map->map[9] = ft_strdup("1111111111");
	map->map[10] = NULL;
	map->len = 10;
	map->lines = 10;
	map->size_x = map->len * 10;
	map->size_y = map->lines * 10;
	close_mapfile(map);
	db_print_tex_info(data->tex);
}
