#include "../../inc/test.h"

static	void	flood_clean(char **m_cp, bool **check, t_cell *queue, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(check[i]);
		i++;
	}
	free(check);
	free(queue);
	free_array(m_cp);
}

static	void	set_dx_dy(int d[4], char axis)
{
	if (axis == 'x')
	{
		d[0] = -1;
		d[1] = 0;
		d[2] = 1;
		d[3] = 0;
	}
	if (axis == 'y')
	{
		d[0] = 0;
		d[1] = 1;
		d[2] = 0;
		d[3] = -1;
	}
}

bool	check_surr(t_map *map, t_cell *queue, int *back, t_cell curr)
{
	curr.i = 0;
	while (curr.i < 4)
	{
		curr.ny = curr.y + curr.dy[curr.i];
		curr.nx = curr.x + curr.dx[curr.i];
		if (curr.ny < 0 || curr.ny >= map->lines + 2 || curr.nx < 0
			|| curr.nx >= map->len + 2
			|| curr.checked[curr.ny][curr.nx] == true)
		{
			curr.i++;
			continue ;
		}
		if (curr.m_cp[curr.ny][curr.nx] != '1' && curr.m_cp[curr.ny][curr.nx]
			!= ' ' && curr.m_cp[curr.ny][curr.nx] != 'X')
			return (false);
		if (curr.m_cp[curr.ny][curr.nx] == ' ')
		{
			curr.checked[curr.ny][curr.nx] = true;
			queue[(*back)++] = (t_cell){.y = curr.ny, .x = curr.nx};
		}
		curr.i++;
	}
	return (true);
}

void	flood_fill(t_map *map, char **map_copy, bool **checked, t_cell *queue)
{
	int		front;
	int		back;
	t_cell	current;
	
	front = 0;
	back = 0;
	queue[back++] = (t_cell){.y = 0, .x = 0};
	checked[0][0] = true;
	while (front < back)
	{
		current = queue[front++];
		current.m_cp = map_copy;
		current.checked = checked;
		set_dx_dy(current.dx, 'x');
		set_dx_dy(current.dy, 'y');
		map_copy[current.y][current.x] = 'X';
		if (check_surr(map, queue, &back, current) == false)
		{
			flood_clean(map_copy, checked, queue, map->lines + 2);
			exit_game(map->data, true, ERROR_20);
		}
	}
	flood_clean(map_copy, checked, queue, map->lines + 2);
}

void	validate_map_walls(t_map *map, char **map_copy)
{
	int		i;
	int		s_map_copy;
	bool	**checked;
	t_cell	*queue;

	i = 0;
	s_map_copy = (map->lines + 2) * (map->len + 2);
	checked = ft_calloc(map->lines + 2, sizeof(bool*));
	queue = ft_calloc(s_map_copy, sizeof(t_cell));
	if (!checked || !queue)
		exit_game(map->data, true, ERROR_19);
	while (i < map->lines + 2)
	{
		checked[i] = ft_calloc(map->len + 2, sizeof(bool));
		if (!checked[i])
			exit_game(map->data, true, ERROR_19);
		i++;
	}
	flood_fill(map, map_copy, checked, queue);
}
