/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:49 by npolack           #+#    #+#             */
/*   Updated: 2024/11/22 17:29:45 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



int	free_all(char **object, int i)
{
	while (--i >= 0)
		free(object[i]);
	free(object);
	return (0);
}

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

int	init_collectable(t_data *game)
{
	int	i, j, k;

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
					game->item[k].pos.x = i * game->map.def;
					game->item[k].pos.y = j * game->map.def;
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

int load_images(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->items_nb)
	{
		game->item[i].img = new_file_img("./image/item.xpm", game);
		if (!game->item[i].img.img)
			return (0);
	}
	game->exit.img = new_file_img("./image/exit.xpm", game);
	if (!game->exit.img.img)
		return (0);
	game->hero.face[0] = new_file_img("./image/sprite1.xpm", game);
	game->hero.face[1] = new_file_img("./image/sprite2.xpm", game);
	game->hero.face[2] = new_file_img("./image/sprite3.xpm", game);
	game->hero.face[3] = new_file_img("./image/sprite4.xpm", game);
	if (!game->hero.face[0].img || !game->hero.face[1].img
		   	|| !game->hero.face[2].img || !game->hero.face[3].img)
		return (0);
	game->map.ground = new_file_img("./image/ground.xpm", game);
	if (!game->map.ground.img)
		return (0);
	game->map.wall = new_file_img("./image/wall.xpm", game);
	if (!game->map.wall.img)
		return (0);
	return (1);
}

int	game_init(t_data *game, char *path, int def)
{	
	int		i, j;
	void	*mlx;
	void	*win;

	if (!init_map(game, path, def))
		return (0);
	game->height = game->map.h * game->map.def;
	game->width = game->map.w * game->map.def;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "HZD$");
	if (!game->win)
		return (0);
	if (!game->mlx || !game->win)
		return (0);
	game->img = new_img(game->width, game->height, game);
	if (!init_hero(game))
		return (0);
	if (!init_collectable(game))
		return (0);
	if (!init_exit(game))
		return (0);
	if (!check_map(game))
	{
		ft_printf("Map is invalid !\n");
		return (0);
	}
	if (!load_images(game))
		return (0);
	i = -1;
    while (++i < 99999)
		game->key_states[i] = 0;
	return (1);
}
