/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:44:31 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 13:44:48 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_junk_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1')
		return (true);
	return (false);
}

int	rgb_color_conversion(void *mlx, int r, int g, int b)
{
	int	color;
	int	mlx_color;

	color = (r << 16) | (g << 8) | b;
	mlx_color = mlx_get_color_value(mlx, color);
	return (mlx_color);
}

bool	open_mapfile(t_map *map)
{
	map->fd = open(map->map_file, O_RDONLY);
	if (map->fd == -1)
		return (false);
	return (true);
}

void	close_mapfile(t_map *map)
{
	close(map->fd);
	map->fd = -1;
}
