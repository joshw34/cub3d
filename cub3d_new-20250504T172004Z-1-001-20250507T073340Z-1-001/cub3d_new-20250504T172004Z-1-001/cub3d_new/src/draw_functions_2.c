/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 19:20:00 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/07 12:14:32 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
static void DB_print_ray(t_ray **ray)
{
    int i = 0;

    while (ray[i])
    {
        printf("ray %i distance %f from the wall (%i , %i) \n", i, ray[i]->distance, ray[i]->wall_x, ray[i]->wall_y);
        ++i;
    }
}

static void rendering(t_game *game, t_ray *ray, int x)
{
int y = game->length - 1;
int i = 0;
int distance = (int)ray->distance;
int wall_size = game->length - (distance * 2);
printf("pixel at thwe adress %p y == %i ray distance == %i game size_line == %i and pixel is = %i \n", game->pixel_array_3d, y, distance, game->size_line, x + (y - i) * game->size_line / 4 );



while (i < game->length)
{
    if ( i < distance / 2)
        game->pixel_array_3d[x + (y - i) * game->size_line / 4 ] = BLUE;
    else if (i < distance  / 2 + wall_size)
        game->pixel_array_3d[x + (y - i) * game->size_line / 4 ] = RED;
    else
        game->pixel_array_3d[x + (y - i) * game->size_line / 4 ] = GREEN;
    ++i;
}/*


while (i <  ray->distance && i < game->length / 2)
{
    game->pixel_array_3d[x + (y - i) * game->size_line / 4 ] = BLUE;
    
    ++i;
}

while (wall_size >= 0 && ((y- i) >= 0))
{
    printf("pixel at thwe adress %p y == %i ray distance == %i game size_line == %i and pixel is = %i wall_size  =%i et i =%i \n", game->pixel_array_3d, y, distance, game->size_line, x + (y - i) * game->size_line / 4, wall_size, i );

    game->pixel_array_3d[x + (y - i) * game->size_line / 4 ] = GREEN;
//printf("pixel at thwe adress %p y == %i ray distance == %i game size_line == %i and pixel is = %i \n", game->pixel_array_3d, y, distance, game->size_line, x + (y - i) * game->size_line / 4 );

    --wall_size;
    ++i;  
}

while((y- i) >= 0)
{
    game->pixel_array_3d[x + (y - i) * game->size_line / 4 ] = BLUE;
    ++i;  
}
*/

}

void draw_ray(t_game *game, float angle, long long int color, t_ray *ray)
{
    float xo = game->player.x;
    float yo = game->player.y;
    float err = 0;
   
    (ray)->sum_of_dx = 0;
   (ray)->sum_of_dy = 0;
    (ray)->angle = angle;
    while (is_drawable((int)(xo + game->player.dx), (int)(yo + game->player.dy), game) && !is_a_wall((int)(xo + game->player.dx), (int)(yo + game->player.dy), game, ray))
        {
            put_pixel(game, xo, yo, GREEN);
            err += angle;
            if (err > 0.5)
            {
                err -= 1;
                yo += sin(angle);
               (ray)->sum_of_dy += sin(angle);
            }
            (ray)->sum_of_dx += cos(angle);
            xo += cos(angle);
        }
       
        (ray)->distance = sqrt((ray)->sum_of_dx * (ray)->sum_of_dx + (ray)->sum_of_dy * (ray)->sum_of_dy);
}

void draw_fov(t_game *game, float middle_angle, long long int color)
{
    //float angle;
   int i = game->width / 2 - 1;
    float FOV_rad = FOV * PI / 180;
    float angle_incrementation = FOV_rad / game->width;
    int number_of_ray;
    float angle = middle_angle;
    t_ray ray;
   printf("angle incr == %f\n", angle_incrementation);
    if (angle < 0)
        angle += 2 * PI;
    else if (angle > 2 * PI)
        angle -=  2 * PI;

    int ray_count = 0;
    //while (i <= FOV_rad / 2)
    printf("angle incr == %i\n", i);
    while (i >= 0)
    {
        angle -= angle_incrementation;
        if (angle < 0)
            angle += 2 * PI;
      
        draw_ray(game, angle, color, &ray);
        rendering(game, &ray, i);
        --i;
        ++ray_count;
    }
   i = game->width/ 2;
   angle = middle_angle;
    while (i < game->length)
    {
        if (angle > 2 * PI)
            angle -= 2 * PI;
        draw_ray(game, angle, color, &ray);
        rendering(game, &ray, i);
        angle += angle_incrementation;
        ++i;
        ++ray_count;
    }
   printf("ray_count == %i\n" ,ray_count);
   printf("game->length = %i\n", game->length);
   //sleep(1);
    //DB_print_ray(game->fov);



}
/*

void draw_ray(t_game *game, float angle, long long int color)
{
    float xo = game->player.x;
    float yo = game->player.y;
    float err = 0;
    //if (!angle)
      //  angle = game->player.angle;
     

    while (is_drawable((int)(xo + game->player.dx), (int)(yo + game->player.dy), game) && !is_a_wall((int)(xo + game->player.dx), (int)(yo + game->player.dy), game))
        {
            put_pixel(game, xo, yo, GREEN);
            err += angle;
            if (err > 0.5)
            {
                err -= 1;
                //yo += game->player.dy;
                yo += sin(angle);
            }
            //xo += game->player.dx;
            xo += cos(angle);
        }
}

void draw_fov(t_game *game, float angle, long long int color)
{
    //float angle;
    float i = 0;
    float rad = 0.01;
    float ray = angle;
    //angle = game->player.angle - 0.3;

    if (angle < 0)
        angle += 2 * PI;
    else if (angle > 2 * PI)
        angle -=  2 * PI;

    int ray_count = 0;
    while (i < 0.53)
    {
        ray -= rad;
        if (ray < 0)
            ray += 2 * PI;
        //printf("print up ray = %f from angle == %f\n",ray, angle);
        draw_ray(game, ray, color);
        i+= 0.01023;
        ++ray_count;
    }

    i = 0;
    
   ray = angle;
    while (i < 0.53)
    {
        ray += rad;
        if (ray > 2 * PI)
            ray -= 2 * PI;
       //printf("print down ray = %f from angle == %f\n",ray, angle);
        draw_ray(game, ray, color);
        i+= 0.01023;
        ++ray_count;
    }
    //printf("ray_count == %i\n",ray_count);
}
*/