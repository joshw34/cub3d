/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:42:26 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 12:42:27 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_game_struct(t_data *data)
{
	if (data->game->bg_img)
		mlx_destroy_image(data->init, data->game->bg_img);
	if (data->game->game_img)
		mlx_destroy_image(data->init, data->game->game_img);
	free(data->game);
}

void	free_tex_struct(t_data *data)
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

void	free_map_struct(t_data *data)
{
	if (data->map->map)
		free_array(data->map->map);
	if (data->map->fd >= 0)
		close(data->map->fd);
	free(data->map);
}
