/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:08:03 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/22 15:49:19 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static t_texture_img	*which_texture(t_data *data)
{
	if (data->ray->ra <= PI / 2 && data->ray->ra >= 0)
	{
		if (data->game->direction == 'h')
			return (&(data->tex_set->textures_set[1]));
		return (&(data->tex_set->textures_set[2]));
	}
	else if (data->ray->ra >= PI / 2 && data->ray->ra <= PI)
	{
		if (data->game->direction == 'h')
			return (&(data->tex_set->textures_set[1]));
		return (&(data->tex_set->textures_set[3]));
	}
	else if (data->ray->ra <= 3 * (PI / 2) && data->ray->ra >= PI)
	{
		if (data->game->direction == 'h')
			return (&(data->tex_set->textures_set[0]));
		return (&(data->tex_set->textures_set[3]));
	}
	else
	{
		if (data->game->direction == 'h')
			return (&(data->tex_set->textures_set[0]));
		return (&(data->tex_set->textures_set[2]));
	}
}

long long int	get_texel_value(t_data *data)
{
	t_texture_img	*texture;
	int				texel_column;
	float			texel_line;
	long long int	texel_value;

	texture = which_texture(data);
	texel_column = which_texel_column(data->game, data->ray, texture);
	texel_line = ((float)data->game->start_y
			-(float)data->game->start_y_first_value)
		* ((float)texture->length / (float)data->game->line_h);
	if (!(texture->tex_addr))
		texture->tex_addr = (int *)mlx_get_data_addr(texture->tex_img,
				&texture->bpp, &texture->size_line, &texture->endian);
	texel_value = texture->tex_addr[(int)texel_line
		* texture->size_line / 4 + texel_column];
	return (texel_value);
}
