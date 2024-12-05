/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:50:08 by npolack           #+#    #+#             */
/*   Updated: 2024/12/05 18:47:33 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_collectable(t_data *game)
{
	int	j;
	int	i;

	game->items_nb = 0;
	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
			if (game->map.soil[j][i] == 'C')
				game->items_nb++;
	}
	return (game->items_nb);
}

int	check_map(t_data *game)
{
	int	j;
	int	x;
	int	y;

	x = game->hero.pos.x / game->map.def;
	y = game->hero.pos.y / game->map.def;
	if (!init_flooded_map(game))
		return (0);
	flood_map(game, x, y);
	if (!map_cmp(game) || game->map.h < 3 || game->map.w < 3)
		return (0);
	if (game->map.h > 20 || game->map.w > 20)
		return (0);
	if (!check_exit_and_collectible(game))
		return (0);
	return (1);
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

int	check_exit_and_collectible(t_data *game)
{
	int	i;
	int	j;
	int	exit;
	int	collectible;

	exit = 0;
	collectible = count_collectable(game);
	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
		{
			if (game->map.soil[j][i] == 'E')
			{
				if (exit)
					return (0);
				exit = 1;
			}
		}
	}
	if (!exit || !collectible)
		return (0);
	return (1);
}
