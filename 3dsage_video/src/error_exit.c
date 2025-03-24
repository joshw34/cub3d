# include "../inc/3dsage.h"

static	void	free_data(t_data *data)
{
	if (data->bg)
		mlx_destroy_image(data->init, data->bg);
	if (data->win)
		mlx_destroy_window(data->init, data->win);
	if (data->init)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	free(data);
}

void	exit_game(t_data *data, char *msg)
{
	if (data)
		free_data(data);	
	if (msg)
	{
		printf("Error: ");
		printf("%s\n", msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
