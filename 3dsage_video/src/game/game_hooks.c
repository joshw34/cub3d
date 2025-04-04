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
//	init_map(data);
//	db_show_first_hit(data);
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
