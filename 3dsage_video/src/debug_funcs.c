#include "../inc/test.h"

void	db_show_first_hit(t_data *data)
{
	mlx_put_image_to_window(data->init, data->map_win, data->ray->y_hit_img, data->ray->rx - 5, data->ray->ry - 5);
}

void	db_show_both_hits(t_data *data)
{
	if ((data->ray->h_rx > 0 && data->ray->h_rx < 641) && (data->ray->h_ry > 0 && data->ray->h_ry < 641))
		mlx_put_image_to_window(data->init, data->map_win, data->ray->y_hit_img, data->ray->h_rx - 5, data->ray->h_ry - 5);
	if ((data->ray->v_rx > 0 && data->ray->v_rx < 641) && (data->ray->v_ry > 0 && data->ray->v_ry < 641))
		mlx_put_image_to_window(data->init, data->map_win, data->ray->y_hit_img, data->ray->v_rx - 5, data->ray->v_ry - 5);
}
void	db_print_player_x_y(t_player *player)
{

	float	p_x;
	float	p_y;
	float	p_ang;
	int		x_pos;
	int		y_pos;

	p_x	= player->p_x;
	p_y = player->p_y;
	p_ang = player->p_ang;
	x_pos = floor(p_x / 64.0);
	y_pos = floor(p_y / 64.0);
	printf("\n");
	printf("p_x: %f\tp_y: %f\tp_ang: %f\n", p_x, p_y, p_ang);
	printf("p_xpos: %d\tp_ypos: %d\n", x_pos, y_pos);
	printf("\n");
}

void	db_draw_line(t_data *data, t_player *play)
{
	int		n_pixels;
	double	pixel_x;
	double	pixel_y;
	double	delta_x;
	double	delta_y;

	delta_x = play->p_dx * 525;
	delta_y = play->p_dy * 525;
	n_pixels = sqrt((delta_x * delta_x) + delta_y * delta_y);
	delta_x /= n_pixels;
	delta_y /= n_pixels;
	pixel_x = (double)play->p_x;
	pixel_y = (double)play->p_y;
	while (n_pixels)
	{
		mlx_pixel_put(data->init, data->map_win, pixel_x, pixel_y, RED);
		pixel_x += delta_x;
		pixel_y += delta_y;
		n_pixels--;
	}
}

void	db_print_pdx_pdy(t_player *p)
{
	printf("\n");
	printf("px = %f\tpy = %f\n", p->p_x, p->p_y);
	printf("pdx = %f\tpdy = %f\n", p->p_dx, p->p_dy);
	printf("p_ang = %f\n", p->p_ang);
	printf("\n");
}

void	db_err_print(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
}

static	void	db_print_top_btm(int n, bool add_spaces)
{
	if (add_spaces == true)
		n = (n * 2) + 1;
	else
		n = n + 2;
	while (n > 0)
	{
		ft_printf("*");
		n--;
	}
	ft_printf("\n");
}

static	void	db_print_map_array(t_data *data, bool add_spaces)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map->map;
	db_print_top_btm(data->map->len, add_spaces);
	while (map[i])
	{
		j = 0;
		ft_printf("*");
		while (map[i][j])
		{
			ft_printf("%c", map[i][j]);
			if (map[i][j + 1] && add_spaces == true)
				ft_printf(" ");
			j++;
		}
		ft_printf("*\n");
		i++;
	}
	db_print_top_btm(data->map->len, add_spaces);
}

void	db_print_map_info(t_data *data, bool add_spaces)
{
	ft_printf("\n######MAP INFO######\n");
	ft_printf("Map File: %s\n", data->map->map_file);
	ft_printf("Lines: %d\n", data->map->lines);
	ft_printf("Longest: %d\n", data->map->len);
	ft_printf("####################\n");
	if (data->map->map_file)
		db_print_map_array(data, add_spaces);
}

void	db_print_tex_info(t_tex *tex)
{
	ft_printf("NO: %s\n", tex->NO);
	ft_printf("SO: %s\n", tex->SO);
	ft_printf("EA: %s\n", tex->EA);
	ft_printf("WE: %s\n", tex->WE);
	ft_printf("C: %d\n", tex->C);
	ft_printf("F: %d\n", tex->F);
}
