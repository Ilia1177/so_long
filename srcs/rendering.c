/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:19:56 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 16:04:45 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	render(void *data)
{
	static int	count;

	check_items(data);
	check_mob(data);
	draw_map(data);
	moves_on_screen(data);
	handle_input(data);
	draw_collectable(data);
	draw_exit(data);
	draw_hero(data);
	if (count > SPEED_MOB)
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
	t_point	pos;
	int		frame;
	t_img	img;

	frame = game->hero.frame;
	pos = make_point(game->hero.pos.x, game->hero.pos.y);
	img = game->hero.face[frame];
	put_img_to_game(game, img, pos.x, pos.y);
}

void	draw_collectable(t_data *game)
{
	t_img	img;
	int		x;
	int		y;
	int		i;

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
	int		def;
	int		i;
	int		j;

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
				put_img_to_game(game, wa, i * def, j * def);
			else
				put_img_to_game(game, gr, i * def, j * def);
		}
	}
}
