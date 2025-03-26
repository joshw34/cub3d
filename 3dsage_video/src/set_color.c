#include "../inc/test.h"

static	void	set_player(t_data *data, int x, int y)
{
	char	*addr;
	int		*pixel;

	addr = mlx_get_data_addr(data->player, &data->bpp, &data->ln_len,
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

static	void	set_background(t_data *data, int x, int y)
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
			if (y < (MAPY / 2))
				*pixel = 0x042f66;
			else
				*pixel = 0x21961b;
			x++;
		}
		x = 0;
		y++;
	}
}

void	set_image_data(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	set_background(data, x, y);
	set_player(data, x, y);
}
