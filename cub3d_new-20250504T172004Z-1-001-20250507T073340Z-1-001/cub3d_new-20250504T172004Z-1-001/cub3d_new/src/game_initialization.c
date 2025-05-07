/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_initialization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cngogang <cngogang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:12:15 by cngogang          #+#    #+#             */
/*   Updated: 2025/05/07 11:16:51 by cngogang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
static t_ray **malloc_fov(t_game *game)
{
	 t_ray **fov_mem_space;
	 int 	i;

	 i = 0;

	 fov_mem_space = malloc(sizeof(t_ray *) * (game->width + 1));
	 fov_mem_space[game->width] = 0;

	 while ( i < game->width)
	 {
		fov_mem_space[i] = malloc(sizeof(t_ray));
		++i;
	 }
	 return (fov_mem_space);
	 
}

 void init_game(t_game *game)
{
    game->mlx = mlx_init();
    mlx_get_screen_size(game->mlx, &(game->width), &(game->length));
    game->window = mlx_new_window(game->mlx, game->width, game->length, "CUB3D");
	game->window_3d = mlx_new_window(game->mlx, game->width, game->length, "CUB3D");
    game->img = mlx_new_image(game->mlx, game->width, game->length );
    game->pixel_array = (int *)mlx_get_data_addr(game->img, &(game->bpp), &(game->size_line), &(game->endian));
    
	//game->window = mlx_new_window(game->mlx, game->width, game->length, "CUB3D");
    game->img_3d = mlx_new_image(game->mlx, game->width, game->length );
    game->pixel_array_3d = (int *)mlx_get_data_addr((game->img_3d), &(game->bpp), &(game->size_line), &(game->endian));
	game->player.x = game->width / 2;
    game->player.y = game->length / 2;
	game->player.dx = 0;
    game->player.dy = 0;
	//game->fov = malloc_fov(game);
	//printf("f\n");
}



static void	execute_keyboard(int key_code, t_game *game)
{
	if (key_code == 119 || key_code == 65362)
		{
		if (is_drawable(game->player.x + game->player.dx, game->player.y + game->player.dy, game))
		{
			(game->player.y)+=game->player.dy * 4;
			(game->player.x)+=game->player.dx * 4;
		}
			
		}
		//move_up(param, step);
	if (key_code == 97 || key_code == 65361)
		{
			//if (game->player.x > 0)
			//	(game->player.x)-= (1 + 10 * sprint);;
				
            game->player.angle -= 0.1;
			if(game->player.angle < 0)
				game->player.angle += 2 *PI;
			game->player.dx=cos(game->player.angle);
			game->player.dy=sin(game->player.angle);
                
                

		}
		//move_left(param, step);
      if (key_code == 100 || key_code == 65363)
		{
				//if (game->player.x < game->width)
				  // (game->player.x)+= (1 + 10 * sprint);	
           game->player.angle += 0.1;
			if(game->player.angle > 2 * PI)
				game->player.angle -= 2 *PI;
			game->player.dx=cos(game->player.angle);
			game->player.dy=sin(game->player.angle);
	
		}
		//move_right(param, step);
	if (key_code == 115 || key_code == 65364)
		{

		if (is_drawable(game->player.x + game->player.dx, game->player.y + game->player.dy, game))
			{
			(game->player.y)-=game->player.dy * 4;
			(game->player.x)-=game->player.dx * 4;
			} 
		}
	game = (t_game *)game;
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_image(game->mlx, game->img_3d);
	game->img = mlx_new_image(game->mlx, game->width, game->length);
	game->img_3d = mlx_new_image(game->mlx, game->width, game->length);
    game->pixel_array = (int *)mlx_get_data_addr(game->img, &(game->bpp), &(game->size_line), &(game->endian));
	game->pixel_array_3d = (int *)mlx_get_data_addr(game->img_3d, &(game->bpp), &(game->size_line), &(game->endian));
	draw_map(game);
	draw_circle(game, 20, game->player.x, game->player.y, GREEN);
	draw_fov(game, game->player.angle ,RED);
	mlx_put_image_to_window(game->mlx, game->window, game->img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window_3d, game->img_3d, 0, 0);
	//printf("HERE\n");
	//
}
int	execute_keyboard_command(int key_code, void *game)
{
	execute_keyboard(key_code, game );
	return (1);
}
 