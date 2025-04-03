#include "../../inc/test.h"

/* Radians = 0 -> 2PI. Reset angle to 2PI when reaching zero as negative is invalid*/
/* See pdx_pdy diagram */
static	void	look(int key, t_player *play)
{
	if (key == RT)
	{
		play->p_ang += 0.1;
		if (play->p_ang > 2 * PI)
			play->p_ang -= (2 * PI);
		play->p_dx = cos(play->p_ang) * 5;
		play->p_dy = sin(play->p_ang) * 5;
	}
	else if (key == LT)
	{
		play->p_ang -= 0.1;
		if (play->p_ang < 0)
			play->p_ang += (2 * PI);
		play->p_dx = cos(play->p_ang) * 5;
		play->p_dy = sin(play->p_ang) * 5;
	}
}

/* See px_py_move diagram */
static	void	move(int key, t_player *play)
{
	if (key == W)
	{
		play->p_x += play->p_dx;
	    play->p_y += play->p_dy;
	}
	else if (key == S)
	{	
		play->p_x -= play->p_dx;
	    play->p_y -= play->p_dy;
	}
	else if (key == A)
	{
		play->p_x += play->p_dy;
	    play->p_y -= play->p_dx;
	}
	else if (key == D)
	{
		play->p_x -= play->p_dy;
	    play->p_y += play->p_dx;
	}
}

int	key(int keysym, t_data *data)
{
	if (keysym == LT || keysym == RT)
		look(keysym, data->player);
	else if (keysym == W || keysym == A || keysym == S || keysym == D)
		move(keysym, data->player);
	else
		return (-1);
	raycasting(data);
	printf("\n");
	printf("p_x: %f\tp_y: %f\tp_ang: %f\n", data->player->p_x, data->player->p_y, data->player->p_ang);
	printf("p_xpos: %d\tp_ypos: %d\n", (int)data->player->p_x / 64, (int)data->player->p_y / 64);
	printf("rx: %f\try: %f\tra: %f\n", data->ray->rx, data->ray->ry, data->ray->ra);
	printf("rmx: %d\trmy: %d\n", data->ray->mx, data->ray->my);
	printf("\n");
	init_map(data);
	db_show_both_hits(data);
	//mlx_put_image_to_window(data->init, data->win, data->ray->y_hit_img, data->ray->rx, data->ray->ry);
	//mlx_put_image_to_window(data->init, data->win, data->ray->y_hit_img, data->ray->h_rx - 5, data->ray->h_ry - 5);
	//mlx_put_image_to_window(data->init, data->win, data->ray->y_hit_img, data->ray->v_rx - 5, data->ray->v_ry - 5);
	return (0);
}

/* This can probably be removed and init_map() called directly */
int	expose_win(t_data *data)
{
	init_map(data);
	return (0);
}

int	win_close(t_data *data)
{
	exit_game(data, false, "Game Over: User Closed Window\n");
	return (0);
}
