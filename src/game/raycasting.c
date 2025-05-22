/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:21:29 by jwhitley          #+#    #+#             */
/*   Updated: 2025/05/22 15:19:48 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* This is the same for h and v, moved her to avoid repetition.
   if player is facing exactly left/right no horizontal walls will be hit, if
   facing up/down no vertical will be hit. in this case, we set the rx and ry
   to the player location and stop searching by setting dof to 20. Otherwise we
   check for hits in the loop, if its not a wall, we add the offset and check
   again.*/
static	void	cast_common(t_ray *ray, t_player *play, t_map *map, char dir)
{
	if (((ray->ra == 0 || ray->ra - PI == 0) && dir == 'h')
		|| ((ray->ra == PI / 2 || ray->ra == (3 * PI) / 2) && dir == 'v'))
	{
		ray->rx = play->p_x;
		ray->ry = play->p_y;
		ray->dof = 100;
	}
	while (ray->dof < 100)
	{
		map_pixel_to_array(ray);
		//printf("ray->mx == %i && ray->my == %i\n", ray->mx, ray->my);
		if ((ray->mx >= 0 && ray->mx < map->len)
			&& (ray->my >= 0 && ray->my < map->lines)
			&& map->map[ray->my][ray->mx] == '1')
			found_wall(ray, play, dir);
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			ray->dof++;
		}
	}
}

/* Similar to cast_h however on -tan is needed here */
static	void	cast_v(t_player *play, t_ray *ray, t_map *map)
{
	float	n_tan;

	ray->dof = 0;
	n_tan = -tan(ray->ra);
	if (ray->ra > (PI / 2) && ray->ra < (3 * PI) / 2)
	{
		ray->rx = (((int)play->p_x >> 6) << 6) - 0.0001;
		ray->ry = (play->p_x - ray->rx) * n_tan + play->p_y;
		ray->xo = -64;
		ray->yo = -ray->xo * n_tan;
	}
	else if (ray->ra < (PI / 2) || ray->ra > (3 * PI) / 2)
	{
		ray->rx = (((int)play->p_x >> 6) << 6) + 64;
		ray->ry = (play->p_x - ray->rx) * n_tan + play->p_y;
		ray->xo = 64;
		ray->yo = -ray->xo * n_tan;
	}
	cast_common(ray, play, map, 'v');
}

/* Looking up / down to find the horizontal wall collisions
   dof = depth of field, sets a limit on the number of squares to check
   ry = the top of the square that the player is currently in
   rx = the distance travelled in the x direction when travelling along the
   player looking angle to the next horizontal collision
   if this does not hit a wall, we add offsets and check again:
   yo = y offset to next horizontal wall = 1 square
   xo = x offset to next horizontal wall collison */
static	void	cast_h(t_player *play, t_ray *ray, t_map *map)
{
	float	a_tan;

	ray->dof = 0;
	a_tan = -1 / tan(ray->ra);
	if (ray->ra > PI)
	{
		ray->ry = (((int)play->p_y >> 6) << 6) - 0.0001;
		ray->rx = (play->p_y - ray->ry) * a_tan + play->p_x;
		ray->yo = -64;
		ray->xo = -ray->yo * a_tan;
	}
	else if (ray->ra < PI)
	{
		ray->ry = (((int)play->p_y >> 6) << 6) + 64;
		ray->rx = (play->p_y - ray->ry) * a_tan + play->p_x;
		ray->yo = 64;
		ray->xo = -ray->yo * a_tan;
	}
	cast_common(ray, play, map, 'h');
}

/* ray->r = counter for rays (set to 60 rays per frame)
   ray->ra = ray angle. This is the player facing angle plus offset
   init_map is called first so the ray hits can be placed on top of it, this
   can be moved to bottom of function for final version
   memcpy bg->game erases the previous frame from the buffer, the walls can then
   be drawn on top */
void	raycasting(t_data *data, t_ray *ray, t_player *player, t_game *game)
{
	ray->r = 0;
	printf("Before RA == %f\n",ray->ra);
	ray->ra = player->p_ang - deg_to_rad(30);
	if (ray->ra < 0)
		ray->ra += (2 * PI);
	if (ray->ra > 2 * PI)
		ray->ra -= (2 * PI);
	printf("after RA == %f\n",ray->ra);
	ft_memcpy(game->game_addr, game->bg_addr, game->total_bytes);
	while (ray->r < 1200)
	{
		printf("2.5 angle = %.8f r_value == %i\n", data->ray->ra, data->ray->r);
		printf("3 angle = %.8f r_value == %i\n", data->ray->ra, data->ray->r);
		reset_ray_data(ray);
		cast_h(player, ray, data->map);
		cast_v(player, ray, data->map);
		find_closest_hit(ray, game);
		fix_fisheye(ray, player);
		printf("1 angle = %.8f r_value == %i\n", data->ray->ra, data->ray->r);
		set_walls(data, game, ray->r);
		set_next_angle(ray);
		printf("2 angle = %.8f r_value == %i\n", data->ray->ra, data->ray->r);
		ray->r++;
	}
	init_map(data, game);
}
