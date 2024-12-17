/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:06:32 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 12:54:03 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	init_flooded_map(t_data *game)
{
	int	w;
	int	h;
	int	i;
	int	j;

	w = game->map.w;
	h = game->map.h;
	game->flooded_map.h = h;
	game->flooded_map.w = w;
	game->flooded_map.soil = malloc(sizeof(char *) * h);
	if (!game->flooded_map.soil)
		return (0);
	j = -1;
	while (++j < h)
	{
		game->flooded_map.soil[j] = malloc(sizeof (char) * w);
		if (!game->flooded_map.soil[j])
			return (free_all(game->flooded_map.soil, j));
		i = -1;
		while (++i < w)
			game->flooded_map.soil[j][i] = '0';
	}
	return (1);
}

int	flood_map(t_data *game, int i, int j)
{
	int		h;
	int		w;

	w = game->map.w;
	h = game->map.h;
	if (j < 0 || j >= h)
		return (0);
	else if (i < 0 || i >= w)
		return (0);
	else if (game->map.soil[j][i] == '1')
		return (0);
	else if (game->flooded_map.soil[j][i] == 'V')
		return (0);
	else
	{
		game->flooded_map.soil[j][i] = 'V';
		flood_map(game, i + 1, j);
		flood_map(game, i, j + 1);
		flood_map(game, i - 1, j);
		flood_map(game, i, j - 1);
	}
	return (1);
}
