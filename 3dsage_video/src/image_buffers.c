#include "../inc/test.h"

/*static	void	set_map(t_data *data, int *bits_per_pixel, int *size_line, int *endian)
}*/

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
			*pixel = 0xb92537;
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

	addr = mlx_get_data_addr(data->bg, &data->bpp, &data->ln_len,
			&data->endian);
	while (y < MAPY)
	{
		while (x < MAPX)
		{
			pixel = (int *)(addr + (y * data->ln_len + x * (data->bpp / 8)));
			*pixel = color;
			x++;
		}
		x = 0;
		y++;
	}
}

void	set_image_data(t_data *data)
{
	set_player(data, 0, 0);
	set_background(data, 0, 0, WHITE);
	//set_map(data->map, x, y, WHITE);
}
