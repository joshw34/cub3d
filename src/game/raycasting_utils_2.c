/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwhitley <jwhitley@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:29:03 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/14 13:30:32 by jwhitley         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* set the ray angle for next raycast loop. correct value if out of bounds */
void	set_next_angle(t_ray *ray)
{
	ray->ra += 0.0008726646;
	if (ray->ra < 0)
		ray->ra += (2 * PI);
	if (ray->ra > 2 * PI)
		ray->ra -= (2 * PI);
}

/* fixes the fisheye effect caused by the different ray lengths */
void	fix_fisheye(t_ray *ray, t_player *player)
{
	float	corrected_ra;

	corrected_ra = player->p_ang - ray->ra;
	if (corrected_ra < 0)
		corrected_ra += (2 * PI);
	if (corrected_ra > 2 * PI)
		corrected_ra -= (2 * PI);
	ray->d_ray = ray->d_ray * cos(corrected_ra);
}

/*Chooses whether the vertical or horizontal hit is closest. rx, ry are now
  correct, d_ray will change in fix_fisheye() */
void	find_closest_hit(t_ray *ray, t_game *game)
{
	if (ray->d_h < ray->d_v)
	{
		ray->rx = ray->h_rx;
		ray->ry = ray->h_ry;
		ray->d_ray = ray->d_h;
		game->direction = 'h';
	}
	else
	{
		ray->rx = ray->v_rx;
		ray->ry = ray->v_ry;
		ray->d_ray = ray->d_v;
		game->direction = 'v';
	}
}
