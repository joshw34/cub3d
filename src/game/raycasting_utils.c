#include "../../inc/cub3d.h"

float	ray_len(t_ray *ray, t_player *play)
{
	float	len;

	len = (sqrt((ray->rx - play->p_x) * (ray->rx - play->p_x) + (ray->ry - play->p_y) * (ray->ry - play->p_y)));
	return (len);
}

/* if a wall was found we save the x and y location for either vertical or horizontal and dof to max to stop further searching */
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
	ray->dof = 100;
}

/* for every rx and ry we calculate the array coordiante from the pixel location. if the pixel
   is outside the screen, we set the array coord to -1 to prevent checking the array and segfaulting */
void	map_pixel_to_array(t_ray *ray)
{
	float	temp;
	int		width;
	int		height;

	width = ray->data->map->len * 64;
	height = ray->data->map->lines * 64;
	if ((ray->rx < 1 || ray->rx > width) || (ray->ry < 1 || ray->ry > height))
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

/* resets the values in ray struct for each of the 60 rays
   distances set to int max to ensure real hits wil be lower
   others set to -1 to ensure that no array checking is done if a wall isnt found */
void	reset_ray_data(t_ray *ray)
{
	ray->dH = 2147483647.0;
	ray->dV = 2147483647.0;
	ray->v_rx = -1;
	ray->v_ry = -1;
	ray->h_rx = -1;
	ray->h_ry = -1;
}
