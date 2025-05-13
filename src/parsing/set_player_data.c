#include "../../inc/test.h"

static	void	player_details(t_player *p, t_map *m, int i, int j)
{
	char	c;

	c = m->map[i][j];
	p->p_x = j * 64;
	p->p_y = i * 64;
	if (c == 'N')
		p->p_ang = (PI * 3) * 0.5;
	else if (c == 'S')
		p->p_ang = PI * 0.5;
	else if (c == 'E')
		p->p_ang = 0;
	else if (c == 'W')
		p->p_ang = PI;
	p->p_dx = cos(p->p_ang) * 5;
	p->p_dy = sin(p->p_ang) * 5;
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
