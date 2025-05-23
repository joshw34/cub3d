/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_texel_col.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:08:03 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/22 15:49:19 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static	int	fourth_quadran(t_ray *ray, t_texture_img *txtr, int w_s, char dir)
{
	if (dir == 'h')
		return (((w_s - fmod(ray->rx, w_s)) / w_s) * (float)txtr->width);
	return ((fmod(ray->ry, w_s) / w_s) * (float)txtr->width);
}

static	int	third_quadran(t_ray *ray, t_texture_img *txtr, int w_s, char dir)
{
	if (dir == 'h')
		return (((w_s - fmod(ray->rx, w_s)) / w_s) * (float)txtr->width);
	return (((w_s - fmod(ray->ry, w_s)) / w_s) * (float)txtr->width);
}

static	int	second_quadran(t_ray *ray, t_texture_img *txtr, int w_s, char dir)
{
	if (dir == 'h')
		return ((fmod(ray->rx, w_s) / w_s) * (float)txtr->width);
	return (((w_s - fmod(ray->ry, w_s)) / w_s) * (float)txtr->width);
}

static	int	first_quadran(t_ray *ray, t_texture_img *txtr, int w_s, char dir)
{
	if (dir == 'h')
		return ((fmod(ray->rx, w_s) / w_s) * (float)txtr->width);
	return ((fmod(ray->ry, w_s) / w_s) * (float)txtr->width);
}

int	which_texel_column(t_game *game, t_ray *ray, t_texture_img *texture)
{
	float	wall_size;

	wall_size = 64.0;
	if (ray->ra <= PI / 2 && ray->ra >= 0)
		return (first_quadran(ray, texture, wall_size, game->direction));
	else if (ray->ra >= PI / 2 && ray->ra <= PI)
		return (second_quadran(ray, texture, wall_size, game->direction));
	else if (ray->ra <= 3 * (PI / 2) && ray->ra >= PI)
		return (third_quadran(ray, texture, wall_size, game->direction));
	else if (ray->ra >= 3 * (PI / 2) && ray->ra <= 2 * PI)
		return (fourth_quadran(ray, texture, wall_size, game->direction));
	return (0);
}
