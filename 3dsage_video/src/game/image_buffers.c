#include "../../inc/test.h"

/* Draw each tile. Currently set to 64x64 pixels*/
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

/* Cycle through map array, send x + y pixel for top-left corner of each tile */
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
				set_map2(data, j * 64, i * 64, WHITE);
			else if (map[i][j] == '1')
				set_map2(data, j * 64, i * 64, GREEN);
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

static	void	set_background(t_data *data, int x, int y, int color)
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
			*pixel = rgb_color_conversion(data->init, 0, 0, 0);
			x++;
		}
		x = 0;
		y++;
	}
}

/* Set image buffer data for all images. Needs to be tidied up */
void	set_image_data(t_data *data)
{
	set_background(data, 0, 0, BLACK);
	set_player(data, 0, 0);
	set_map(data);
}
