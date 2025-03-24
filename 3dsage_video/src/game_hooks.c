#include "../inc/3dsage.h"

int	key(int keysym, t_data *data)
{

}

int	expose_win(t_data *data)
{
	init_map(data);
}

int	win_close(t_data *data)
{
	exit_game(data, false, "Game Over: User Closed Window\n");
	return (0);
}
