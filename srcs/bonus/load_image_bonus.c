/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:17:17 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 12:54:59 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	load_items_images(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->items_nb)
	{
		game->item[i].img = new_file_img("./textures/item.xpm", game);
		if (!game->item[i].img.img)
		{
			while (--i >= 0)
				mlx_destroy_image(game->mlx, game->item[i].img.img);
			free_image(game, game->counter.num, 10);
			return (0);
		}
	}
	return (1);
}

int	load_hero_images(t_data *game)
{
	game->hero.face[0] = new_file_img("./textures/h1.xpm", game);
	game->hero.face[1] = new_file_img("./textures/h2.xpm", game);
	game->hero.face[2] = new_file_img("./textures/h3.xpm", game);
	game->hero.face[3] = new_file_img("./textures/h4.xpm", game);
	if (!game->hero.face[0].img || !game->hero.face[1].img
		|| !game->hero.face[2].img || !game->hero.face[3].img)
		return (0);
	return (1);
}

int	load_map_images(t_data *game)
{
	game->map.ground = new_file_img("./textures/ground.xpm", game);
	if (!game->map.ground.img)
		return (0);
	game->map.wall = new_file_img("./textures/wall.xpm", game);
	if (!game->map.wall.img)
		return (0);
	return (1);
}

int	load_images(t_data *game)
{
	if (!load_counter_images(game))
		return (0);
	if (!load_items_images(game))
		return (0);
	game->exit.img = new_file_img("./textures/exit.xpm", game);
	if (!game->exit.img.img)
		return (0);
	if (!load_hero_images(game))
		return (0);
	if (!load_map_images(game))
		return (0);
	return (1);
}
