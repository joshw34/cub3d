#include "../../inc/test.h"

static	void	look(int key, t_player *play)
{
	if (key == LT)
	{
		play->p_ang -= 0.1;
		if (play->p_ang < 0)
			play->p_ang += (2 * PI);
		play->p_dx = cos(play->p_ang) * 5;
		play->p_dy = sin(play->p_ang) * 5;
	}
	else if (key == RT)
	{
		play->p_ang += 0.1;
		if (play->p_ang > 2 * PI)
			play->p_ang -= (2 * PI);
		play->p_dx = cos(play->p_ang) * 5;
		play->p_dy = sin(play->p_ang) * 5;
	}
}

static	void	move(int key, t_player *play)
{
	if (key == W)  // Forward
	{
		play->p_x += play->p_dx;
	    play->p_y += play->p_dy;
	}
	else if (key == S)  // Backward
	{	
		play->p_x -= play->p_dx;
	    play->p_y -= play->p_dy;
	}
	else if (key == A)  // Left (strafe)
	{
		play->p_x -= play->p_dy;
	    play->p_y -= play->p_dx;  // Fixed: MINUS for Y-down systems
	}
	else if (key == D)  // Right (strafe)
	{
		play->p_x += play->p_dy;
	    play->p_y += play->p_dx;  // Fixed: PLUS for Y-down systems
	}
}

int	key(int keysym, t_data *data)
{
	if (keysym == LT || keysym == RT)
		look(keysym, data->player);
	if (keysym == W || keysym == A || keysym == S || keysym == D)
		move(keysym, data->player);
	else
		return (-1);
	init_map(data);
	return (0);
}

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
