/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:42:01 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/22 16:27:53 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

static	void	free_data(t_data *data)
{
	if (data->map)
		free_map_struct(data);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->tex)
		free_tex_struct(data);
	if (data->game)
		free_game_struct(data);
	if (data->rc_win)
		mlx_destroy_window(data->init, data->rc_win);
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
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (msg)
		ft_putstr_fd(msg, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
