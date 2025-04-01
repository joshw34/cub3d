#include "../../inc/test.h"
#include <stdio.h>

void	map_pixel_to_array(t_ray *ray)
{
	float	temp;

	temp = ray->rx / 64.0;
	ray->mx = floor(temp);
	temp = ray->ry / 64.0;
	ray->my = floor(temp);
	printf("rx: %f\try: %f\n", ray->rx, ray->ry);
	ft_printf("mx: %d\tmy: %d\n", ray->mx, ray->my);
}

/* Horizontal */
void	raycasting(t_player *play, t_ray *ray, t_map *map)
{
	printf("!!!!!!!!!!!!!!!!");
	float	aTan;

	ray->ra = play->p_ang;
	ray->r = 0;
	while (ray->r < 1)
	{
		ray->dof = 0;
		aTan = -1 / tan(ray->ra);
		if (ray->ra > PI)
		{
			ray->ry = (((int)play->p_y >> 6) << 6)-0.0001;
			ray->rx = (play->p_y - ray->ry) * aTan + play->p_x;
			ray->yo = -64;
			ray->xo = -ray->yo * aTan;
		}
		if (ray->ra < PI)
		{
			ray->ry = (((int)play->p_y >> 6) << 6) + 64;
			ray->rx = (play->p_y - ray->ry) * aTan + play->p_x;
			ray->yo = 64;
			ray->xo = ray->yo * aTan;
		}
		if (ray->ra == 0 || ray->ra == PI)
		{
			ray->rx = play->p_x;
			ray->ry = play->p_y;
			ray->dof = 8;
		}
		while (ray->dof < 6)
		{
			map_pixel_to_array(ray);
			if (map->map[ray->my][ray->mx] == '1')
			{
				printf("found wall\n");
				ray->dof = 6;
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
	db_print_player_x_y(play);
	map_pixel_to_array(ray);
}
