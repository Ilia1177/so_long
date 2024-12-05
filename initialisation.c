/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:49 by npolack           #+#    #+#             */
/*   Updated: 2024/12/05 17:29:54 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_map(t_data *game, char *path, int def)
{
	char	*mapline;
	
	game->map.def = def;
	if(!measure_map(&game->map, path))
		return (0);
	if(!make_soil(&game->map, path))
		return (0);
	return (1);
}

int	init_collectable(t_data *game)
{
	int	i;
	int	j;
	int	k;

	if (count_collectable(game))
	{
		game->item = (t_item *)malloc(sizeof(t_item) * game->items_nb);
		if (!game->item)
			return (0);
		k = 0;
		j = -1;
		while (++j < game->map.h)
		{
			i = -1;
			while (++i < game->map.w)
			{
				if (game->map.soil[j][i] == 'C')
				{
					game->item[k].exist = 1;
					game->item[k].width = 50;
					game->item[k].height = 50;
					game->item[k].pos = make_point(i * game->map.def, j * game->map.def);
					k++;
				}
			}
		}
	}
	return (1);
}

int	init_exit(t_data *game)
{
	int	i, j;

	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
		{
			if (game->map.soil[j][i] == 'E')
			{
				game->exit.pos.x = i * game->map.def;
				game->exit.pos.y = j * game->map.def;
				break ;
			}
		}
	}
	return (1);
}

int	init_hero(t_data *game)
{
	int		i, j;

	game->hero.frame = 0;
	game->hero.width = 40;
	game->hero.height = 40;
	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
		{
			if (game->map.soil[j][i] == 'P')
			{
				game->hero.pos.x = i * game->map.def;
				game->hero.pos.y = j * game->map.def;
				break ;
			}
		}
	}
	return (1);
}

int	game_init(t_data *game, char *path, int def)
{	
	int	i;

	if (!init_map(game, path, def))
		return (0);
	game->height = game->map.h * game->map.def;
	game->width = game->map.w * game->map.def;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->width, game->height, "HZD$");
	if (!game->win)
		return (0);
	game->img = new_img(game->width, game->height, game);
	if (!init_hero(game) || !init_collectable(game) || !init_exit(game))
		return (0);
	if (!check_map(game) || !init_mob(game) || !load_images(game))
		return (0);
	i = -1;
    while (++i < 99999)
		game->key_states[i] = 0;
	return (1);
}
