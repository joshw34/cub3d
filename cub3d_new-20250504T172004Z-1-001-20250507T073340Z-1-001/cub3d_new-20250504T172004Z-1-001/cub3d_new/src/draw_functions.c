/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:32:28 by cngogang          #+#    #+#             */
/*   Updated: 2025/04/30 14:52:24 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void put_pixel(t_game *game, int x, int y, long long int color)
{
    int pixel_position;

    pixel_position = x + y * game->size_line / 4;
    if (x < 0 || y < 0 || x > game->width || y > game->length )
        return ;
    if (pixel_position < 0 || pixel_position > game->width * game->length)
        return   ;
   // printf("x == %f, y ==%f   width =-= %i length == %i size_line== %i\n", game->player.x, game->player.y, game->width, game->length, game->size_line);
    game->pixel_array[x + y * game->size_line / 4 ] = color;
    
}

void draw_full_block(t_game *game, int x, int y)
{
    int block_width;
    int block_length;
    int i;
    int j;

    block_width = game->width / game->map.x_max;
    block_length = game->length / game->map.y_max;
    j = 0;
    i = 0;

    while (j < block_length)
    {
        i = 0;
        while (i < block_width)
        {
            game->pixel_array[(x * block_width) + i + (y * block_length + j) * game->size_line / 4 ] = BLUE;
            ++i;
        }
        ++j;
    }


}

void draw_edge_block(t_game *game, int x, int y)
{
    int block_width;
    int block_length;
    int i;
    int j;

    block_width = game->width / game->map.x_max;
    block_length = game->length / game->map.y_max;
    j = 0;
    i = 0;

    while (j < block_length)
    {
        game->pixel_array[(x * block_width) + 0 + (y * block_length + j) * game->size_line / 4 ] = BLUE;
        game->pixel_array[(x * block_width) + block_width - 1  + (y * block_length + j) * game->size_line / 4 ] = BLUE;
        ++j;
    }

    while (i < block_width)
    {
        game->pixel_array[(x * block_width) + i + (y * block_length + 0) * game->size_line / 4 ] = BLUE;
        game->pixel_array[(x * block_width) + i  + (y * block_length + block_length - 1) * game->size_line / 4 ] = BLUE;
        ++i;
    }

}

void draw_map_block(t_game *game, int x, int y)
{
    int block_index;

    block_index = x + game->map.x_max * y;
    if (game->map.map[block_index] == 1)
        draw_full_block(game, x, y);
    else if (game->map.map[block_index] == 0)
        draw_edge_block(game, x, y);
}


void draw_map(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;

    while (y < game->map.y_max)
    {
        x = 0;
        while (x < game->map.x_max)
        {
            draw_map_block(game, x, y);
            ++x;
        }
        ++y;
    }
    //draw_circle(game, 30, game->player.x, game->player.y, RED);
}

void draw_circle_2(t_game *game)
{
	int rayon = 10;
	int x = 0;
	int y = rayon;
	int m = 5 - 4 * rayon;
	int center_x =  (int)game->player.x;
	int center_y = (int)game->player.y;
	while (x <= y)
	{
	game->pixel_array[center_x - x + (center_y + y)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x + x + (center_y + y)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x + y + (center_y + x)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x + y + (center_y - x)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x + x + (center_y - y)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x - x + (center_y - y)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x - y + (center_y - x)* game->size_line / 4] = 16711680;
	game->pixel_array[center_x - y + (center_y + x)* game->size_line / 4] = 16711680;
	if (m > 0)
		{
			--y;
			m -= 8*y;
		} 
		++x;
		m += 8*x +4;	
	}
}


void draw_circle(t_game *game, int rayon, int xo, int yo, long long int color)
{

	int x = 0;
	int y = rayon;
	int m = 5 - 4 * rayon;

	while (x <= y)
	{
    put_pixel(game, xo - x, yo + y, color);
    put_pixel(game, xo + x, yo + y, color);
    put_pixel(game, xo + y, yo + x, color);
    put_pixel(game, xo + y, yo - x, color);
    put_pixel(game, xo + x, yo - y, color);
    put_pixel(game, xo - x , yo -y, color);
    put_pixel(game, xo -y , yo - x, color);
    put_pixel(game, xo -y , yo + x, color);
	if (m > 0)
		{
			--y;
			m -= 8*y;
		} 
		++x;
		m += 8*x +4;	
	}
}