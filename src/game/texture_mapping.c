/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:08:03 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/22 15:49:19 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"
static t_texture_img   *which_texture(t_data *data)
{
    if (data->ray->ra <= PI / 2 && data->ray->ra >= 0)
    {
        if (data->game->direction == 'h')
            return (&(data->tex_set->textures_set[1]));
        return (&(data->tex_set->textures_set[2]));         

    }
    else if (data->ray->ra >= PI / 2 && data->ray->ra <= PI)
    {
         if (data->game->direction == 'h')
            return (&(data->tex_set->textures_set[1]));
        return (&(data->tex_set->textures_set[3]));     
    }
    else if (data->ray->ra <= 3 * (PI / 2) && data->ray->ra >= PI)
    {
        if (data->game->direction == 'h')
            return (&(data->tex_set->textures_set[0]));
        return (&(data->tex_set->textures_set[3]));  
    }
    else if (data->ray->ra >=  3 * (PI / 2) && data->ray->ra <= 2 * PI)
    {
        if (data->game->direction == 'h')
            return (&(data->tex_set->textures_set[0]));
        return (&(data->tex_set->textures_set[2])); 
    }
    return (0);
}
static int which_texel_column(t_data *data, t_texture_img *texture)
{
    float wall_size;
   // printf("ray->angle == %f game-direction == %c, ray->rx = %f ray->ry = %f , row number %i game->line_h %i and ray_count == %i\n",data->ray->ra, data->game->direction, data->ray->rx, data->ray->ry, data->game->start_y - data->game->start_y_first_value, data->game->line_h,  data->ray->r);
    wall_size = 64,0;
    if (data->ray->ra <= PI / 2 && data->ray->ra >= 0)
    {
        if (data->game->direction == 'h')
            return ((fmod(data->ray->rx, wall_size) / wall_size) * (float)texture->width);
        return ((fmod(data->ray->ry, wall_size) / wall_size) * (float)texture->width); 
        /*if (data->game->direction == 'h')
            return ((fmod(data->ray->rx, wall_size) / wall_size) * (float)texture->width);
        return (((fmod(data->ray->ry, wall_size) / wall_size) * (float)texture->width);         
        */        

    }
    else if (data->ray->ra >= PI / 2 && data->ray->ra <= PI)
    {
         if (data->game->direction == 'h')
            return ((fmod(data->ray->rx, wall_size) / wall_size) * (float)texture->width);
        return (((wall_size - fmod( data->ray->ry, wall_size)) / wall_size) * (float)texture->width);     
    }
    else if (data->ray->ra <= 3 * (PI / 2) && data->ray->ra >= PI)
    {
        if (data->game->direction == 'h')
            return (((wall_size - fmod( data->ray->rx, wall_size)) / wall_size) * (float)texture->width);
        return (((wall_size - fmod( data->ray->ry, wall_size)) / wall_size)* (float)texture->width);  
    }
    else if (data->ray->ra >=  3 * (PI / 2) && data->ray->ra <= 2 * PI)
    {
        if (data->game->direction == 'h')
            return (((wall_size - fmod( data->ray->rx, wall_size)) / wall_size) * (float)texture->width);
        return ((fmod(data->ray->ry, wall_size) / wall_size) * (float)texture->width); 
    }
    printf("return O\n");
    return (0);
}

long long int get_texel_value(t_data *data)
{
    
    t_texture_img   *texture;
    int             texel_column;
    float           texel_line;
    long long int             texel_value;

    
    texture = which_texture(data);
    texel_column = which_texel_column(data, texture);
    //printf("texture_column == %i\n",texel_column);
    texel_line = ((float)data->game->start_y - (float)data->game->start_y_first_value) * ((float)texture->length / (float)data->game->line_h);
    //printf("texture_width == %i and texture_length == %i\n", texture->width, texture->length);
    if (!(texture->tex_addr))
        texture->tex_addr = (int *)mlx_get_data_addr(texture->tex_img, &texture->bpp,
			&texture->size_line, &texture->endian);
    //printf("texel line (int) == %i texel_line %f texture_size line == %i texel_column == %i  bpp = %i and the whole thing is %i\n", (int)texel_line, texel_line, texture->size_line, texel_column, texture->bpp, (int)texel_line * texture->size_line + texel_column * (texture->bpp / 8));
    //int texel_position = (int)texel_line * texture->size_line + texel_column * (texture->bpp / 8);
    //if (texel_position < 64 * 64)
    texel_value = texture->tex_addr[(int)texel_line * texture->size_line / 4 + texel_column];
    //else
      //  texel_value = 0;
        //printf("texel_value == %lli\n",texel_value);
    return (texel_value);
    // texel_value = texture->tex_addr[(int)texel_line * texture->size_line / 4 + texel_column * (texture->bpp / 8)];
}
