/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:38:33 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/21 11:41:10 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* Everything needed to draw the final 3d image */
void	init_game_struct(t_data *data)
{
	data->game = ft_calloc(1, sizeof(t_game));
	if (!data->game)
		exit_game(data, true, ERROR_8);
	data->game->data = data;
}

/* All variables necessary for raycasting. */
void	init_ray_struct(t_data *data)
{
	data->ray = ft_calloc(1, sizeof(t_ray));
	if (!data->ray)
		exit_game(data, true, ERROR_7);
	data->ray->data = data;
}

void	init_texture_struct(t_data *data)
{
	data->tex = ft_calloc(1, sizeof(t_tex));
	if (!data->tex)
		exit_game(data, true, ERROR_6);
	data->tex->data = data;
	data->tex->f = -1;
	data->tex->c = -1;
}

void	init_player_struct(t_data *data)
{
	data->player = ft_calloc(1, sizeof(t_player));
	data->player->data = data;
}

void	init_map_struct(t_data *data, char *map_file)
{
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		exit_game(data, true, ERROR_2);
	data->map->map_file = map_file;
	data->map->lines = 0;
	data->map->len = -1;
	data->map->data = data;
}
