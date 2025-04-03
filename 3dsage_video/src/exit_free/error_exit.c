#include "../../inc/test.h"

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

static	void	free_textures(t_data *data)
{
	if (data->textures->NO)
		free(data->textures->NO);
	if (data->textures->SO)
		free(data->textures->SO);
	if (data->textures->EA)
		free(data->textures->EA);
	if (data->textures->WE)
		free(data->textures->WE);
	free(data->textures);
}

static	void	free_map_player_ray(t_data *data)
{
	if (data->map->map)
		free_array(data->map->map);
	if (data->map->m_img)
		mlx_destroy_image(data->init, data->map->m_img);
	free(data->map);
	if (data->player->p_img)
		mlx_destroy_image(data->init, data->player->p_img);
	free(data->player);
	if (data->ray)
	{
		mlx_destroy_image(data->init, data->ray->y_hit_img);
		free(data->ray);
	}
}

static	void	free_data(t_data *data)
{
	if (data->map || data->player || data->ray)
		free_map_player_ray(data);
	if (data->textures)
		free_textures(data);
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

/* Used for normal and error exits, free all data, if error = true, prints Error: before message to stderr,
   prints msg to stdout if no error*/
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
