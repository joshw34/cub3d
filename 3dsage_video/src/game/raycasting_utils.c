#include "../../inc/test.h"

float	ray_len(t_ray *ray, t_player *play)
{
	float	len;

	len = (sqrt((ray->rx - play->p_x) * (ray->rx - play->p_x) + (ray->ry - play->p_y) * (ray->ry - play->p_y)));
	return (len);
}

void	found_wall(t_ray *ray, t_player *play, char direction)
{
	if (direction == 'v')
	{
		ray->v_rx = ray->rx;
		ray->v_ry = ray->ry;
		ray->dV = ray_len(ray, play);
	}
	if (direction == 'h')
	{
		ray->h_rx = ray->rx;
		ray->h_ry = ray->ry;
		ray->dH = ray_len(ray, play);
	}
	ray->dof = 20;
}

void	map_pixel_to_array(t_ray *ray)
{
	float	temp;

	if ((ray->rx < 1 || ray->rx > 640) || (ray->ry < 1 || ray->ry > 640))
	{
		ray->mx = -1;
		ray->my = -1;
		return ;
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
}

float	deg_to_rad(int deg)
{
	float	rad;

	rad = deg * (PI / 180);
	return (rad);
}

void	reset_ray_data(t_ray *ray)
{
	ray->dH = 2147483647.0;
	ray->dV = 2147483647.0;
	ray->v_rx = -1;
	ray->v_ry = -1;
	ray->h_rx = -1;
	ray->h_ry = -1;
}
