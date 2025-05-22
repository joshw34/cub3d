/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:41:18 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/22 16:26:56 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void set_texture_img(t_data *data, t_texture_img *texture_img, char *path)
{
    texture_img->tex_img = mlx_xpm_file_to_image(data->init, path, &(texture_img->width), &(texture_img->length));
    printf("1 and img == %p\n", texture_img->tex_img);
    if (!(texture_img->tex_img))
		exit_game(data, true, ERROR_22);
    printf("2\n");
}

void load_texture_img(t_data *data)
{
    data->tex_set = ft_calloc(1, sizeof(t_tex_set));
    data->tex_set->textures_set = ft_calloc(4, sizeof(t_texture_img));
    set_texture_img(data, &(data->tex_set->textures_set[0]), data->tex->no);
    set_texture_img(data, &(data->tex_set->textures_set[1]), data->tex->so);
    set_texture_img(data, &(data->tex_set->textures_set[2]), data->tex->we);
    set_texture_img(data, &(data->tex_set->textures_set[3]), data->tex->ea);
}