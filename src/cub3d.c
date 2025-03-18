#include "../inc/cub3d.h"

static	void	draw_pixels(t_data *data)
{
	int	x = 1;
	int	y = 1;
	int x_low = 10;
	int x_high = 1270;
	int y_low = 10;
	int y_high = 710;
	while(y_low <= y_high)
	{
		x = 1;
		y = 1
		while (x <= x_high)
		{
			if ((y == y_low || y == y_high) && (x >= x_low && x <= x_high))
				mlx_pixel_put(data->init, data->win, x, y, 0xFFFFFF);
			else if ((x == x_low || x == x_high) && (y >= y_low && y <= y_high))
				mlx_pixel_put(data->init, data->win, x, y, 0xFFFFFF);
			x++;
		}
		y_low += 10;
		x_low += 10;
		y_high -=10;
		x_high -= 10;
		printf("x = %d\ny = %d\n", x, y);
	}
	sleep(5);
}

int	main(void)
{
	t_data	*data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (printf("Malloc Failed"), 1);
	data->init = mlx_init();
	data->win = mlx_new_window(data->init, 1280, 720, "TEST WINDOW");
	sleep(1);
	mlx_string_put(data->init, data->win, 640, 360, 0xFFFFFF, "Hello, World");
	sleep(1);
	draw_pixels(data);
	mlx_destroy_window(data->init, data->win);
	mlx_destroy_display(data->init);
	free(data->init);
	free(data);
	return (0);
}
