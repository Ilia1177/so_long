/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:49 by npolack           #+#    #+#             */
/*   Updated: 2024/12/09 22:28:21 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	init_map(t_data *game, char *path, int def)
{
	game->map.def = def;
	if (!measure_map(&game->map, path))
		return (0);
	if (!make_soil(&game->map, path))
		return (0);
	game->items_nb = count_object(game, 'C');
	if (game->items_nb < 1)
		return (free_all(game->map.soil, game->map.h));
	if (count_object(game, 'E') != 1 || count_object(game, 'P') != 1)
		return (free_all(game->map.soil, game->map.h));
	init_hero(game);
	init_exit(game);
	if (!init_collectable(game))
		return (free_all(game->map.soil, game->map.h));
	if (!check_map(game))
	{
		free(game->item);
		return (free_all(game->map.soil, game->map.h));
	}
	return (1);
}

int	init_collectable(t_data *game)
{
	int	i;
	int	j;
	int	k;

	game->item = (t_item *)malloc(sizeof(t_item) * game->items_nb);
	if (!game->item)
		return (0);
	k = -1;
	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
		{
			if (game->map.soil[j][i] == 'C')
			{
				game->item[++k].exist = 1;
				game->item[k].pos.x = i * game->map.def;
				game->item[k].pos.y = j * game->map.def;
				game->item[k].img.img = NULL;
			}
		}
	}
	return (1);
}

int	init_exit(t_data *game)
{
	int	i;
	int	j;

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
				game->exit.img.img = NULL;
				break ;
			}
		}
	}
	return (1);
}

int	init_hero(t_data *game)
{
	int	i;
	int	j;

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

	init_to_zero(game);
	if (!init_map(game, path, def))
	{
		ft_printf("Error\nMap is invalid!\n");
		return (0);
	}
	game->height = game->map.h * game->map.def;
	game->width = game->map.w * game->map.def;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (close_window(game));
	game->win = mlx_new_window(game->mlx, game->width, game->height, "HZD$");
	if (!game->win)
		return (close_window(game));
	if (!init_mob(game))
		return (close_window(game));
	if (!load_images(game))
		return (close_window(game));
	game->img = new_img(game->width, game->height, game);
	if (!game->img.img)
		return (close_window(game));
	i = -1;
	while (++i < 99999)
		game->key_states[i] = 0;
	return (1);
}
