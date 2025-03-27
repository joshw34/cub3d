#include "../inc/test.h"

void	db_err_print(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

static	void	db_print_top_btm(int n, bool add_spaces)
{
	if (add_spaces == true)
		n = (n * 2) + 1;
	else
		n = n + 2;
	while (n > 0)
	{
		ft_printf("*");
		n--;
	}
	ft_printf("\n");
}

static	void	db_print_map_array(t_data *data, bool add_spaces)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map->map;
	db_print_top_btm(data->map->len, add_spaces);
	while (map[i])
	{
		j = 0;
		ft_printf("*");
		while (map[i][j])
		{
			ft_printf("%c", map[i][j]);
			if (map[i][j + 1] && add_spaces == true)
				ft_printf(" ");
			j++;
		}
		ft_printf("*\n");
		i++;
	}
	db_print_top_btm(data->map->len, add_spaces);
}

void	db_print_map_info(t_data *data, bool add_spaces)
{
	ft_printf("\n######MAP INFO######\n");
	ft_printf("Map File: %s\n", data->map->map_file);
	ft_printf("Lines: %d\n", data->map->lines);
	ft_printf("Longest: %d\n", data->map->len);
	ft_printf("####################\n");
	if (data->map->map_file)
		db_print_map_array(data, add_spaces);
}
