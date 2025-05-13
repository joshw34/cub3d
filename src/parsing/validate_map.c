#include "../../inc/test.h"

void	fill_copy(t_map *map, char **copy)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			copy[i + 1][j + 1] = map->map[i][j];
			j++;
		}
		i++;
		j = 0;
	}
}

static	char	**copy_map(t_map *map)
{
	int	i;
	char	**copy;
	
	i = 0;
	copy = ft_calloc(map->lines + 3, sizeof(char *));
	if (!map)
		exit_game(map->data, true, ERROR_18);
	while (i < map->lines + 2)
	{
		copy[i] = ft_calloc(map->len + 3, sizeof(char));
		if (!copy[i])
		{
			free_array(copy);
			exit_game(map->data, true, ERROR_18);
		}
		ft_memset(copy[i], ' ', map->len + 3);
		copy[i][map->len + 2] = '\0';
		i++;
	}
	copy[i] = NULL;
	fill_copy(map, copy);
	return (copy);
}

static	bool	valid_map_char(char c, int *player)
{
	if (c == '1' || c == '0' || c == ' ')
		return (true);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*player)++;
		return (true);
	}
	return (false);
}

void	check_map_content(t_map *m, char **map)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (valid_map_char(map[i][j], &player) == false)
			{
				printf("%s\n", map[i]);
				exit_game(m->data, true, ERROR_13);
			}
			j++;
		}
		i++;
	}
	if (player == 0)
		exit_game(m->data, true, ERROR_16);
	if (player > 1)
		exit_game(m->data, true, ERROR_17);
}

void	validate_map(t_map *map)
{
	char	**map_copy;
	check_map_content(map, map->map);
	map_copy = copy_map(map);
	validate_map_walls(map, map_copy);
}
