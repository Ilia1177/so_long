/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:50:08 by npolack           #+#    #+#             */
/*   Updated: 2024/12/10 18:05:41 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	count_object(t_data *game, int object)
{
	int	j;
	int	i;
	int	objs_nb;

	objs_nb = 0;
	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
			if (game->map.soil[j][i] == object)
				objs_nb++;
	}
	return (objs_nb);
}

int	check_map(t_data *game)
{
	int	x;
	int	y;
	int	correct;

	correct = 1;
	x = game->hero.pos.x / game->map.def;
	y = game->hero.pos.y / game->map.def;
	if (!init_flooded_map(game))
		return (0);
	flood_map(game, x, y);
	if (!map_cmp(game) || game->map.h < 3 || game->map.w < 3)
		correct = -1;
	if (game->map.h > 20 || game->map.w > 20)
		correct = -1;
	if (count_object(game, 'E') != 1 || count_object(game, 'P') != 1)
		correct = -1;
	free_all(game->flooded_map.soil, game->flooded_map.h);
	return (correct);
}

void	check_items(t_data *game)
{
	int		i;
	int		x;
	int		y;
	char	*warning;

	x = game->exit.pos.x - 50;
	y = game->exit.pos.y + 25;
	warning = "You have to get every collectable first!";
	i = 0;
	while (i < game->items_nb)
	{
		if (dist(game->hero.pos, game->item[i].pos) < game->map.def)
			game->item[i].exist = 0;
		i++;
	}
	if (dist(game->hero.pos, game->exit.pos) < 50)
	{
		if (!items_exist(game))
			close_window(game);
		else
			mlx_string_put(game->mlx, game->win, x, y, 0xFFFFFFFF, warning);
	}
}

int	items_exist(t_data *game)
{
	int	i;

	i = 0;
	while (i < game->items_nb)
	{
		if (game->item[i].exist)
			return (1);
		i++;
	}
	return (0);
}

int	check_pos(t_data *game, int x, int y)
{
	int	i;
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
