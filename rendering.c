/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:19:56 by npolack           #+#    #+#             */
/*   Updated: 2024/12/03 12:16:15 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

double	dist(t_point a, t_point b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void	check_items(t_data *game)
{
	int	i;

	i = 0;
	while (i < game->items_nb)
	{
		if (dist(game->hero.pos, game->item[i].pos) < game->map.def)
			game->item[i].exist = 0;
		i++;
	}
	if (dist(game->hero.pos, game->exit.pos) < 10)
		close_window(game);
}
 
int	check_pos(t_data *game, int x, int y)
{
	int i;
	int	j;

	i = x / game->map.def;
	j = y / game->map.def;
	if (x >= game->width || y >= game->height)
		return (0);
	if (x < 0 || y < 0)
		return (0);
	if (game->map.soil[j][i] == '1')
		return (0);
	else if (game->map.soil[j][i])
		return (1);
	return (0);
}

void	refresh(t_data *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int	render(void *data)
{
	static int count;

	handle_input(data);
	check_items(data);
	check_mob(data);
	draw_map(data);
	draw_collectable(data);
	draw_exit(data);
	draw_hero(data);
	if (count > SPEED)
	{
		move_mob(data);
		count = 0;
	}
	draw_mob(data);
	refresh(data);
	count++;
	return (0);
}

void	draw_exit(t_data *game)
{
	put_img_to_game(game, game->exit.img, game->exit.pos.x, game->exit.pos.y);
}

void	draw_hero(t_data *game)
{
	int		x;
	int		y;
	int		frame;
	void	*mlx;
	void	*win;
	void	*data;
	t_img	img;

	frame = game->hero.frame;
	x = game->hero.pos.x;
	y = game->hero.pos.y;
	img = game->hero.face[frame];
	win = game->win;
	mlx = game->mlx;
	put_img_to_game(game, img, x, y);
}

void	draw_collectable(t_data *game)
{
	t_img	img;
	void	*mlx;
	void	*win;
	int		x;
	int		y;
	int		i;

	win = game->win;
	mlx = game->mlx;
	i = -1;
	while (++i < game->items_nb)
	{
		img = game->item[i].img;
		x = game->item[i].pos.x;
		y = game->item[i].pos.y;
		if (game->item[i].exist)
			put_img_to_game(game, img, x, y);
	}
}

void	draw_map(t_data *game)
{
	t_img	wa;
	t_img	gr;
	void	*win;
	void	*mlx;
	int		def;
	int		i, j;

	mlx = game->mlx;
	win = game->win;
	wa = game->map.wall;
	gr = game->map.ground;
	def = game->map.def;
	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
		{
			if (game->map.soil[j][i] == '1')
			//	mlx_put_image_to_window (mlx, win, wa.img, i * def, j * def);
				put_img_to_game(game, wa, i * def, j * def);
			else
			//	mlx_put_image_to_window (mlx, win, wa.img, i * def, j * def);
				put_img_to_game(game, gr, i * def, j * def);
		}
	}
}


int	close_window(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->hero.face[i].img);
	mlx_destroy_image(data->mlx, data->map.ground.img);
	mlx_destroy_image(data->mlx, data->map.wall.img);
	mlx_destroy_image(data->mlx, data->exit.img.img);
	free_mob(data, &data->mob);
	free_all(data->flooded_map.soil, data->map.h);
	free_all(data->map.soil, data->map.h);
	i = -1;
	while (++i < data->items_nb)
		mlx_destroy_image(data->mlx, data->item[i].img.img);
	free(data->item);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
