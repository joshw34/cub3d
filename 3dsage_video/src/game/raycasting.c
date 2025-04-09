#include "../../inc/test.h"

static	void	cast_common(t_ray *ray, t_player *play, t_map *map, char dir)
{
	if (ray->ra == 0 || ray->ra - PI == 0)
	{
		ray->rx = play->p_x;
		ray->ry = play->p_y;
		ray->dof = 20;
	}
	while (ray->dof < 20)
	{
		map_pixel_to_array(ray);
		if ((ray->mx >= 0 && ray->mx < 10) && (ray->my >= 0 && ray->ry)
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

void	raycasting(t_data *data)
{
	data->ray->r = 0;
	data->ray->ra = data->player->p_ang - deg_to_rad(30);
	init_map(data);
	while (data->ray->r < 60)
	{
		reset_ray_data(data->ray);
		cast_h(data->player, data->ray, data->map);
		cast_v(data->player, data->ray, data->map);
		if (data->ray->dH < data->ray->dV)
		{
			data->ray->rx = data->ray->h_rx;
			data->ray->ry = data->ray->h_ry;
			data->ray->dRay = data->ray->dH;
		}
		else
			data->ray->dRay = data->ray->dV;
		db_show_first_hit(data);
		data->ray->r++;
		data->ray->ra += deg_to_rad(1);
		if (data->ray->ra < 0)
			data->ray->ra += (2*PI);
		if (data->ray->ra > 2*PI)
			data->ray->ra -= (2*PI);
	}
}
