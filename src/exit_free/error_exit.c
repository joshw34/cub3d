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

static	void	free_game(t_data *data)
{
	if (data->game->bg_img)
		mlx_destroy_image(data->init, data->game->bg_img);
	if (data->game->game_img)
		mlx_destroy_image(data->init, data->game->game_img);
	free(data->game);
}

static	void	free_textures(t_data *data)
{
	if (data->tex->no)
		free(data->tex->no);
	if (data->tex->so)
		free(data->tex->so);
	if (data->tex->ea)
		free(data->tex->ea);
	if (data->tex->we)
		free(data->tex->we);
	free(data->tex);
}

static	void	free_map_player_ray(t_data *data)
{
	if (data->map->map)
		free_array(data->map->map);
	if (data->map->fd >= 0)
		close(data->map->fd);
	free(data->map);
	if (data->player->p_img)
		mlx_destroy_image(data->init, data->player->p_img);
	free(data->player);
	if (data->ray)
	{
		if (data->ray->y_hit_img)
			mlx_destroy_image(data->init, data->ray->y_hit_img);
		free(data->ray);
	}
}

static	void	free_data(t_data *data)
{
	if (data->map || data->player || data->ray)
		free_map_player_ray(data);
	if (data->tex)
		free_textures(data);
	if (data->game)
		free_game(data);
	if (data->map_win)
		mlx_destroy_window(data->init, data->map_win);
	if (data->rc_win)
		mlx_destroy_window(data->init, data->rc_win);
	if (data->init)
	{
		mlx_destroy_display(data->init);
		free(data->init);
	}
	free(data);
}

/* Used for normal and error exits, free all data. If error = true, print "Error:" & message to stderr.
   No error: prints msg to stdout */
void	exit_game(t_data *data, bool error, char *msg)
{
	if (data)
		free_data(data);
	if (error == true)
	{
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (msg)
		ft_putstr_fd(msg, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
