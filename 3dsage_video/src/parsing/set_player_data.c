#include "../../inc/test.h"

static	void	player_details(t_player *p, t_map *m, int i, int j)
{
	p->p_x = j * 64;
	p->p_y = i * 64;
	(void)m;
}

static	bool	found_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

void	set_player_data(t_data *data, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (found_player(map->map[i][j]) == true)
			{
				player_details(data->player, map, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
