#include "../inc/test.h"

bool	open_mapfile(t_map *map)
{
	map->fd = open(map->map_file, O_RDONLY);
	if (map->fd == -1)
		return (false);
	return (true);
}

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
