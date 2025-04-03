#include "../../inc/test.h"

static	float	ray_len(t_ray *ray, t_player *play)
{
	float	len;

	len = (sqrt((ray->rx - play->p_x) * (ray->rx - play->p_x) + (ray->ry - play->p_y) * (ray->ry - play->p_y)));
	return (len);
}

static	void	map_pixel_to_array(t_ray *ray)
{
	db_err_print("setting map coord");
	float	temp;

	if ((ray->rx < 1 || ray->rx > 640) || (ray->ry < 1 || ray->ry > 640))
	{
		ray->mx = -1;
		ray->my = -1;
		return (db_err_print("No Hit"));
	}
	temp = ray->rx / 64.0;
	if (temp < 1)
		ray->mx = 0;
	else
		ray->mx = (int)temp;
	temp = ray->ry / 64.0;
	if (temp < 1)
		ray->my = 0;
	else
		ray->my = (int)temp;
	printf("map coord: mx %d\tmy %d\n\n", ray->mx, ray->my);
	/*ray->mx = (int)ray->rx / 64;
	ray->my = (int)ray->ry / 64;*/
}

/* Vertical */
static	void	raycasting_v(t_player *play, t_ray *ray, t_map *map, float *dV)
{
	float	nTan;

	ray->ra = play->p_ang;
	ray->r = 0;
	printf("***********************VERTICAL************************************\n");
	while (ray->r < 1)
	{
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
		else if (ray->ra == 0 || ray->ra - PI == 0)
		{
			ray->rx = play->p_x;
			ray->ry = play->p_y;
			ray->dof = 20;
		}
		while (ray->dof < 20)
		{
			printf("rx: %f\try: %f\nxo: %f\tyo: %f\n", ray->rx, ray->ry, ray->xo, ray->yo);
			map_pixel_to_array(ray);
			if ((ray->mx >= 0 && ray->mx < 10) && (ray->my >= 0 && ray->ry) && map->map[ray->my][ray->mx] == '1')
			{
				printf("found wall\n");
				ray->v_rx = ray->rx;
				ray->v_ry = ray->ry;
				*dV = ray_len(ray, play);
				ray->dof = 20;
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof++;
			}
		}
		ray->r++;
	}
}

/* Horizontal */
static	void	raycasting_h(t_player *play, t_ray *ray, t_map *map, float *dH)
{
	float	aTan;

	ray->ra = play->p_ang;
	ray->r = 0;
	printf("***********************HORIZONTAL************************************\n");
	while (ray->r < 1)
	{
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
		else if (ray->ra == 0 || ray->ra - PI == 0)
		{
			ray->rx = play->p_x;
			ray->ry = play->p_y;
			ray->dof = 20;
		}
		while (ray->dof < 20)
		{
			printf("rx: %f\try: %f\nxo: %f\tyo: %f\n", ray->rx, ray->ry, ray->xo, ray->yo);
			map_pixel_to_array(ray);
			if ((ray->mx >= 0 && ray->mx < 10) && (ray->my >= 0 && ray->ry) && map->map[ray->my][ray->mx] == '1')
			{
				printf("found wall\n");
				ray->h_rx = ray->rx;
				ray->h_ry = ray->ry;
				*dH = ray_len(ray, play);
				ray->dof = 20;
			}
			else
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				ray->dof++;
			}
		}
		ray->r++;
	}
}

void	raycasting(t_data *data)
{
	float	dH;
	float	dV;

	dH = 2147483647.0;
	dV = 2147483647.0;
	data->ray->v_rx = -1;
	data->ray->v_ry = -1;
	data->ray->h_rx = -1;
	data->ray->h_ry = -1;
	raycasting_h(data->player, data->ray, data->map, &dH);
	raycasting_v(data->player, data->ray, data->map, &dV);
	printf("dV = %f\ndH = %f\n", dV, dH);
	if (dH < dV)
	{
		data->ray->rx = data->ray->h_rx;
		data->ray->ry = data->ray->h_ry;
	}
}
