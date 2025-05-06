#include "../../inc/test.h"

/* Will be used to convert rgb values from mapfile. Return values to be stored in
   textures struct*/
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

/* Calculate length of map lines, not counting \n which will be removed later */
int	ft_strlen_no_nl(const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] != '\n')
			len++;
		i++;
	}
	return (len);
}
