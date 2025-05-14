/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:43:04 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 13:44:12 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	bool	check_color_value(char	**rgb)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (rgb[i])
	{
		j = 0;
		len = ft_strlen(rgb[i]);
		if (len < 1 || len > 3)
			return (false);
		while (rgb[i][j])
		{
			if (rgb[i][j] < '0' || rgb[i][j] > '9')
				return (false);
			j++;
		}
		j = 0;
		i++;
	}
	if (i != 3)
		return (false);
	return (true);
}

static	bool	set_color(char *line, t_tex *tex, char id)
{
	int		r;
	int		g;
	int		b;
	char	**split;

	if ((id == 'C' && tex->c != -1) || (id == 'F' && tex->f != -1))
		parsing_error(tex->data, ERROR_11, line);
	split = ft_split(line + 2, ',');
	if (!check_color_value(split))
	{
		free_array(split);
		parsing_error(tex->data, ERROR_12, line);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_array(split);
	if (r > 255 || g > 255 || b > 255)
		parsing_error(tex->data, ERROR_12, line);
	if (id == 'C')
		tex->c = rgb_color_conversion(tex->data->init, r, g, b);
	else if (id == 'F')
		tex->f = rgb_color_conversion(tex->data->init, r, g, b);
	return (true);
}

static	bool	set_tex_file(char *line, t_tex *tex, char **file)
{
	if (*file)
		parsing_error(tex->data, ERROR_9, line);
	*file = ft_strdup(line + 3);
	if (access(*file, F_OK) != 0 || access(*file, R_OK) != 0)
		parsing_error(tex->data, ERROR_10, line);
	return (true);
}

static	bool	check_line(char *line, t_tex *tex)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_tex_file(line, tex, &tex->no));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_tex_file(line, tex, &tex->so));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_tex_file(line, tex, &tex->we));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_tex_file(line, tex, &tex->ea));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_color(line, tex, 'C'));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (set_color(line, tex, 'F'));
	else
	{
		if (ft_strlen(line) > 0 && is_junk_line(line))
			parsing_error(tex->data, ERROR_13, line);
	}
	return (false);
}

void	get_textures(t_map *map, t_tex *tex, int *total_lines)
{
	int		count;
	char	*line;
	int		line_len;

	line = get_next_line(map->fd);
	count = 0;
	while (line)
	{
		(*total_lines)++;
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		if (check_line(line, tex))
			count++;
		free(line);
		if (count == 6)
			break ;
		line = get_next_line(map->fd);
	}
	if (count != 6)
		exit_game(map->data, true, ERROR_14);
}
