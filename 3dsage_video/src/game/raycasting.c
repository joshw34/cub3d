#include "../../inc/test.h"

static	void	cast_common(t_ray *ray, t_player *play, t_map *map, char dir)
{
	if (ray->ra == 0 || ray->ra - PI == 0 || ray->ra == PI / 2
		|| ray->ra == (3 * PI) / 2)
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

/* Vertical */
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

/* Horizontal */
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
