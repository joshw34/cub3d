#include "../../inc/test.h"

/* set the ray ang le for the next raycast loop. correct value if out of bounds */
void	set_next_angle(t_ray *ray)
{
	ray->ra += deg_to_rad(1);
	if (ray->ra < 0)
		ray->ra += (2*PI);
	if (ray->ra > 2*PI)
		ray->ra -= (2*PI);
}

/* fixes the fisheye effect caused by the different ray lengths */
void	fix_fisheye(t_ray *ray, t_player *player)
{
	float	corrected_ra;

	corrected_ra = player->p_ang - ray->ra;
	if (corrected_ra < 0)
		corrected_ra += (2*PI);
	if (corrected_ra > 2*PI)
		corrected_ra -= (2*PI);
	ray->dRay = ray->dRay * cos(corrected_ra);
}

/*Chooses whether the vertical or horizontal hit is closest. rx, ry are now correct, dRay will change in fix_fisheye() */
void	find_closest_hit(t_ray *ray)
{
	if (ray->dH < ray->dV)
	{
		ray->rx = ray->h_rx;
		ray->ry = ray->h_ry;
		ray->dRay = ray->dH;
	}
	else
	{
		ray->rx = ray->v_rx;
		ray->ry = ray->v_ry;
		ray->dRay = ray->dV;
	}
}
