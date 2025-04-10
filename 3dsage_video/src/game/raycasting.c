#include "../../inc/test.h"

/* This is the same for h and v, moved her to avoid repetition.
   if player is facing exactly left/right no horizontal walls will be hit, if facing up/down no vertical will be hit.
   in this case, we set the rx and ry to the player location and stop searching by setting dof to 20.
   Otherwise we check for hits in the loop, if its not a wall, we add the offset and check again
   The array size is hardcoded to 10x10, this needs to change dynamically */
static	void	cast_common(t_ray *ray, t_player *play, t_map *map, char dir)
{
	if (((ray->ra == 0 || ray->ra - PI == 0) && dir == 'h')
		|| ((ray->ra == PI / 2 || ray->ra == (3 * PI) / 2) && dir == 'v'))
	{
		ray->rx = play->p_x;
		ray->ry = play->p_y;
		ray->dof = 20;
	}
	while (ray->dof < 20)
	{
		map_pixel_to_array(ray);
		if ((ray->mx >= 0 && ray->mx < 10) && (ray->my >= 0 && ray->my < 10)
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
	float	nTan;

	ray->dof = 0;
	nTan = -tan(ray->ra);
	if (ray->ra > (PI / 2) && ray->ra < (3*PI)/2)
	{
		ray->rx = (((int)play->p_x >> 6) << 6)-0.0001;
		ray->ry = (play->p_x - ray->rx) * nTan + play->p_y;
		ray->xo = -64;
		ray->yo = -ray->xo * nTan;
	}
	else if (ray->ra < (PI/2) || ray->ra > (3*PI)/2) 
	{
		ray->rx = (((int)play->p_x >> 6) << 6) + 64;
		ray->ry = (play->p_x - ray->rx) * nTan + play->p_y;
		ray->xo = 64;
		ray->yo = -ray->xo * nTan;
	}
	cast_common(ray, play, map, 'v');
}

/* Looking up / down to find the horizontal wall collisions
   dof = depth of field, sets a limit on the number of squares to check
   ry = the top of the square that the player is currently in
   rx = the distance travelled in the x direction when travelling along the player looking angle to the next horizontal collision
   if this does not hit a wall, we add offsets and check again:
   yo = y offset to next horizontal wall = 1 square
   xo = x offset to next horizontal wall collison */
static	void	cast_h(t_player *play, t_ray *ray, t_map *map)
{
	float	aTan;

	ray->dof = 0;
	aTan = -1 / tan(ray->ra);
	if (ray->ra > PI) //UP
	{
		ray->ry = (((int)play->p_y >> 6) << 6)-0.0001;
		ray->rx = (play->p_y - ray->ry) * aTan + play->p_x;
		ray->yo = -64;
		ray->xo = -ray->yo * aTan;
	}
	else if (ray->ra < PI) //DOWN
	{
		ray->ry = (((int)play->p_y >> 6) << 6) + 64;
		ray->rx = (play->p_y - ray->ry) * aTan + play->p_x;
		ray->yo = 64;
		ray->xo = -ray->yo * aTan;
	}
	cast_common(ray, play, map, 'h');
}

/* ray->r = counter for rays (set to 60 rays per frame)
   ray->ra = ray angle. This is the player facing angle plus offset
   init_map is called first so the ray hits can be placed on top of it, this can be moved to bottom of function for final version
   memcpy bg->game erases the previous frame from the buffer, the walls can then be drawn on top 
   db_show_first_hit() is only here to show the wall hits from rays, this will be removed later. 
   set walls will not need the 'h' or 'v' when textures are added, this is just to make it easier to see the difference between vert/hor walls now*/
void	raycasting(t_data *data, t_ray *ray, t_player *player, t_game *game)
{
	ray->r = 0;
	ray->ra = player->p_ang - deg_to_rad(30);
	init_map(data);
	ft_memcpy(game->game_addr, game->bg_addr, game->total_bytes);
	while (ray->r < 60)
	{
		reset_ray_data(ray);
		cast_h(player, ray, data->map);
		cast_v(player, ray, data->map);
		find_closest_hit(ray);
		db_show_first_hit(data);
		fix_fisheye(ray, player);
		if (ray->dH < ray->dV)
			set_walls(data, 0, 0, 0, 'h');
		else
			set_walls(data, 0, 0, 0, 'v');
		set_next_angle(ray);
		ray->r++;
	}
}
