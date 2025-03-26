#include "../inc/test.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static	void	free_map(t_data *data)
{
	if (data->map->map)
		free_array(data->map->map);
	free(data->map);
}

static	void	free_data(t_data *data)
{
	if (data->map)
		free_map(data);
	if (data->player)
		mlx_destroy_image(data->init, data->player);
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

void	exit_game(t_data *data, bool error, char *msg)
{
	if (data)
		free_data(data);
	if (error == true)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (msg)
		ft_putstr_fd(msg, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
