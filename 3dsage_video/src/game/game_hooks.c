#include "../../inc/test.h"

/*static	void	check_wall(int keysym, t_data *data)
{

}*/

static	bool	check_move(int keysym, t_data *data)
{
	int	x_lim;
	int	y_lim;

	x_lim = data->map->size_x;
	y_lim = data->map->size_y;
	if ((keysym == W || keysym == UP) && (data->player->p_y - 10) >= 0)
		return (data->player->p_y -= 10, true);
	if (keysym == W || keysym == UP)
		return (data->player->p_y = 0, true);
	if ((keysym == S || keysym == DN) && (data->player->p_y + 20) <= y_lim)
		return (data->player->p_y += 10, true);
	if (keysym == S || keysym == DN)
		return (data->player->p_y = (y_lim - 10), true);
	if ((keysym == A || keysym == LT) && (data->player->p_x - 10) >= 0)
		return (data->player->p_x -= 10, true);
	if (keysym == A || keysym == LT)
		return (data->player->p_x = 0, true);
	if ((keysym == D || keysym == RT) && (data->player->p_x + 20) <= x_lim)
		return (data->player->p_x += 10, true);
	if (keysym == D || keysym == RT)
		return (data->player->p_x = (x_lim - 10), true);
	else
		return (false);
}

int	key(int keysym, t_data *data)
{
	if (check_move(keysym, data) == true)
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
