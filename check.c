/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:50:08 by npolack           #+#    #+#             */
/*   Updated: 2024/12/04 13:53:41 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	check_exit_and_collectible(t_data *game)
{
	int	i, j, exit, collectible;

	exit = 0;
	collectible = 0;
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
			if (game->map.soil[j][i] == 'C')
				collectible++;	
		}
	}
	if (!exit || !collectible)
		return (0);
	return (1);
}

