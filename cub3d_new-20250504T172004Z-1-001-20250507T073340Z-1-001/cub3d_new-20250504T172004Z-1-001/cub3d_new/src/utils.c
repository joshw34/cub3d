/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:46:59 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/02 17:41:01 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		str[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

int is_drawable(int x, int y, t_game *game)
{
	if (x < 0 || y < 0)
		return (0);
	if (x   + y *  game->size_line / 4 > game->width * game->length)
		return (0);
	//printf("here\n");
	return (1);
}

int is_a_wall(int x, int y, t_game *game, t_ray *ray)
{
	int block_width;
	int block_length;

	block_width = game->width / game->map.x_max;
    block_length = game->length / game->map.y_max;
	//printf("pos = %i, map[pos] == %i\n", x / block_width + (y / block_length) * game->map.x_max, game->map.map[x / block_width + (y / block_length) * game->map.x_max]);
	if (game->map.map[x / block_width + (y / block_length) * game->map.x_max] == 1)
		{
			(ray)->wall_x = x / block_width;
			(ray)->wall_y = y / block_length;
 			return (1);
		}
	return (0);
}

void free_fov(t_ray **fov)
{
	t_ray **anchor;

	anchor = fov;
	while (*fov)
	{
		free(*fov);
		++fov;
	}
	free(anchor);
	anchor = NULL;

}
