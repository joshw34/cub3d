/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:38:53 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 13:40:10 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	void	remove_map_nl(t_map *map)
{
	int	i;
	int	len;

	i = 0;
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (map->map[i][len - 1] == '\n')
			map->map[i][len -1] = '\0';
		len = ft_strlen(map->map[i]);
		if (len > map->len)
			map->len = len;
		i++;
	}
}

static	void	copy_map(t_map *map, int total_lines)
{
	int		i;
	int		map_start;
	char	*line;

	i = 0;
	map_start = total_lines - map->lines;
	while (i < map_start)
	{
		line = get_next_line(map->fd);
		free(line);
		i++;
	}
	line = get_next_line(map->fd);
	i = 0;
	while (line && i < map->lines)
	{
		map->map[i] = ft_strdup(line);
		free(line);
		line = get_next_line(map->fd);
		i++;
	}
	map->map[i] = NULL;
	close_mapfile(map);
}

static	bool	is_valid_map_line(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			parsing_error(map->data, ERROR_13, line);
		i++;
	}
	map->lines++;
	return (true);
}

static	void	count_map_lines(t_map *map, int *total_lines)
{
	char	*line;
	int		line_len;

	line = get_next_line(map->fd);
	if (!line)
		exit_game(map->data, true, ERROR_15);
	while (line)
	{
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if (line[0] == '\0')
		{
			(*total_lines)++;
			free(line);
			line = get_next_line(map->fd);
			continue ;
		}
		is_valid_map_line(map, line);
		(*total_lines)++;
		free(line);
		line = get_next_line(map->fd);
	}
}

void	get_map(t_map *map, int *total_lines)
{
	count_map_lines(map, total_lines);
	close_mapfile(map);
	if (!open_mapfile(map))
		exit_game(map->data, true, ERROR_3);
	map->map = ft_calloc(map->lines + 1, sizeof(char *));
	copy_map(map, *total_lines);
	if (!map->map[0])
		exit_game(map->data, true, ERROR_15);
	remove_map_nl(map);
	map->size_x = map->len * 10;
	map->size_y = map->lines * 10;
}
