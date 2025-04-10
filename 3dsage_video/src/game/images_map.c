#include "../../inc/test.h"

/* Draws one cell sent from set_map_img(). Currently set to 64x64. size_x and size_y 
   -1 to show gridlines in final image, will be removed for final version */
static	void	set_map2(t_data *data, int x, int y, int color)
{
	int		*pixel;
	char	*addr;
	int		size_x;
	int		size_y;
	int		start_x;
	
	start_x = x;
	size_x = x + 64 - 1;
	size_y = y + 64 - 1;
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

/* Cycle through map array, send x + y pixel for top-left corner of each tile
   Currently sets each tile as 64x64 pixels, needs to be smaller and dynamically assigned */
void	set_map_img(t_data *data)
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
				set_map2(data, j * 64, i * 64, WHITE);
			else if (map[i][j] == '1')
				set_map2(data, j * 64, i * 64, GREEN);
			j++;
		}
		i++;
	}
}

/* Red square for player location. Currently set to 10x10 pixel. Actual player location is
   top-left corner of square */
void	set_player_img(t_data *data, int x, int y)
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
