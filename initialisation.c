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

int	free_items(t_data *game, int i)
{
	while (i >= 0)
	{
		free(game->item[i].img);
		i--;
	}
	free(game->item);
	return (0);
}
int	count_collectable(t_data *game)
{
	int	j;
	int	i;

	game->items_nb = 0;
	j = -1;
	while (++j < game->height / game->map.def)
	{
		i = -1;
		while (++i < game->width / game->map.def)
			if (game->map.soil[j][i] == 'C')
				game->items_nb++;
	}
	return (game->items_nb);
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
		while (++j < game->height / game->map.def)
		{
			i = -1;
			while (++i < game->width / game->map.def)
			{
				if (game->map.soil[j][i] == 'C')
				{
					game->item[k].exist = 1;
					game->item[k].width = 50;
					game->item[k].height = 50;
					game->item[k].img = mlx_xpm_file_to_image(game->mlx, "./image/item.xpm", &game->item[k].width, &game->item[k].height);
					if (!game->item[k].img)
						return (free_items(game, k));
					game->item[k].pos.x = i * game->map.def;
					game->item[k].pos.y = j * game->map.def;
					k++;
				}
			}
		}
	}
	return (1);
}

int	init_map(t_data *game)
{
	game->map.ground.img = mlx_xpm_file_to_image(game->mlx, "./image/ground.xpm", &game->map.def, &game->map.def);
	if (!game->map.ground.img)
		return (0);
	game->map.wall.img = mlx_xpm_file_to_image(game->mlx, "./image/wall.xpm", &game->map.def, &game->map.def);
	if (!game->map.wall.img)
		return (0);
	return (1);
}

t_img	new_img(int w, int h, t_data *game)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_l, &img.endian);
	img.w = w;
	img.h = h;
	return (img);
}

int	init_hero(t_data *game)
{
	int	i;
	int	j;
	t_img tmp;

	game->hero.face[0] = new_file_img("./image/sprite1.xpm", game);
	game->hero.face[1] = new_file_img("./image/sprite2.xpm", game);
	game->hero.face[2] = new_file_img("./image/sprite3.xpm", game);
	game->hero.face[3] = new_file_img("./image/sprite4.xpm", game);

	if (!game->hero.face[0].img || !game->hero.face[1].img || !game->hero.face[2].img || !game->hero.face[3].img)
		return (0);
	game->hero.frame = 0;
	game->hero.width = 40;
	game->hero.height = 40;
	j = 0;
	while (j < game->height / game->map.def)
	{
		i = 0;
		while (i < game->width / game->map.def)
		{
			if (game->map.soil[j][i] == 'P')
			{
				game->hero.pos.x = i * game->map.def;
				game->hero.pos.y = j * game->map.def;
				break ;
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	game_init(t_data *game)
{	
	int i;
	int j;

	game->height = game->map.height;
	game->width = game->map.width;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "HAZARDOU$ GAME");
	game->img = new_img(game->width, game->height, game);
	if (!game->mlx || !game->win)
		return (0);
	if (!init_map(game))
		return (0);
	if(!init_hero(game))
		return (0);
	if (!init_collectable(game))
		return (0);
	i = -1;
    while (++i < 99999)
		game->key_states[i] = 0;
	refresh(game);
	return (1);
}
