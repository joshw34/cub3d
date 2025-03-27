#include "../../inc/test.h"

static	void	set_map2(t_data *data, int x, int y, int color)
{
	int		*pixel;
	char	*addr;
	int		size_x;
	int		size_y;
	int		start_x;
	
	start_x = x;
	size_x = x + 32;
	size_y = y + 32;
	addr = mlx_get_data_addr(data->map->m_img, &data->bpp, &data->ln_len,
			&data->endian);
	while (y < size_y)
	{
		while (x < size_x)
		{
			pixel = (int *)(addr + (y * data->ln_len + x * (data->bpp / 8)));
			*pixel = color;
			x++;
		}
		x = start_x;
		y++;
	}
}

static	void	set_map(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = data->map->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				set_map2(data, j * 32, i * 32, WHITE);
			else if (map[i][j] == '1')
				set_map2(data, j * 32, i * 32, GREEN);
			j++;
		}
		i++;
	}
}

static	void	set_player(t_data *data, int x, int y)
{
	char	*addr;
	int		*pixel;

	addr = mlx_get_data_addr(data->player->p_img, &data->bpp, &data->ln_len,
			&data->endian);
	while (y < 10)
	{
		while (x < 10)
		{
			pixel = (int *)(addr + (y * data->ln_len + x * (data->bpp / 8)));
			*pixel = RED;
			x++;
		}
		x = 0;
		y++;
	}
}

/*static	void	set_background(t_data *data, int x, int y, int color)
{
	int		*pixel;
	char	*addr;
	(void)color;

	addr = mlx_get_data_addr(data->bg, &data->bpp, &data->ln_len,
			&data->endian);
	while (y < data->map->size_y)
	{
		while (x < data->map->size_x)
		{
			pixel = (int *)(addr + (y * data->ln_len + x * (data->bpp / 8)));
			*pixel = rgb_color_conversion(0, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
}*/

void	set_image_data(t_data *data)
{
	//set_background(data, 0, 0, BLACK);
	//db_err_print("BG set");
	set_player(data, 0, 0);
	db_err_print("Player set");
	set_map(data);
	db_err_print("Map set");
}
