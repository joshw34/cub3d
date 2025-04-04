#include "../../inc/test.h"

static	void	cast_common(t_ray *ray, t_player *play, t_map *map, char dir)
{
	if (ray->ra == 0 || ray->ra - PI == 0)
	{
		db_err_print("5");
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
	db_err_print("Vertical");
	float	nTan;

	ray->ra = play->p_ang;
	ray->r = 0;
	while (ray->r < 1)
	{
		ray->dof = 0;
		nTan = -tan(ray->ra);
		if (ray->ra > (PI / 2) && ray->ra < (3*PI)/2)
		{
			db_err_print("3");
			ray->rx = (((int)play->p_x >> 6) << 6)-0.0001;
			ray->ry = (play->p_x - ray->rx) * nTan + play->p_y;
			ray->xo = -64;
			ray->yo = -ray->xo * nTan;
		}
		else if (ray->ra < (PI/2) || ray->ra > (3*PI)/2) 
		{
			db_err_print("4");
			ray->rx = (((int)play->p_x >> 6) << 6) + 64;
			ray->ry = (play->p_x - ray->rx) * nTan + play->p_y;
			ray->xo = 64;
			ray->yo = -ray->xo * nTan;
		}
		cast_common(ray, play, map, 'v');
		ray->r++;
	}
}

/* Horizontal */
static	void	cast_h(t_player *play, t_ray *ray, t_map *map)
{
	db_err_print("Horizontal");
	float	aTan;

	ray->ra = play->p_ang;
	ray->r = 0;
	while (ray->r < 1)
	{
		ray->dof = 0;
		aTan = -1 / tan(ray->ra);
		if (ray->ra > PI) //UP
		{
			db_err_print("1");
			ray->ry = (((int)play->p_y >> 6) << 6)-0.0001;
			ray->rx = (play->p_y - ray->ry) * aTan + play->p_x;
			ray->yo = -64;
			ray->xo = -ray->yo * aTan;
		}
		else if (ray->ra < PI) //DOWN
		{
			db_err_print("2");
			ray->ry = (((int)play->p_y >> 6) << 6) + 64;
			ray->rx = (play->p_y - ray->ry) * aTan + play->p_x;
			ray->yo = 64;
			ray->xo = -ray->yo * aTan;
		}
		cast_common(ray, play, map, 'h');
		ray->r++;
	}
}

void	raycasting(t_data *data)
{
	db_err_print("START");
	reset_ray_data(data->ray);
	cast_h(data->player, data->ray, data->map);
	cast_v(data->player, data->ray, data->map);
	if (data->ray->dH == data->ray->dV)
		printf("SHIT\n");
	if (data->ray->dH < data->ray->dV)
	{
		data->ray->rx = data->ray->h_rx;
		data->ray->ry = data->ray->h_ry;
	}
	init_map(data);
	db_show_first_hit(data);
}
