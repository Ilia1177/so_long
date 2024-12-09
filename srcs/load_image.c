/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:17:17 by npolack           #+#    #+#             */
/*   Updated: 2024/12/09 22:05:25 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	load_counter_images(t_data *game)
{
	int	i;

	game->counter.num[0] = new_file_img("./textures/num/0.xpm", game);
	game->counter.num[1] = new_file_img("./textures/num/1.xpm", game);
	game->counter.num[2] = new_file_img("./textures/num/2.xpm", game);
	game->counter.num[3] = new_file_img("./textures/num/3.xpm", game);
	game->counter.num[4] = new_file_img("./textures/num/4.xpm", game);
	game->counter.num[5] = new_file_img("./textures/num/5.xpm", game);
	game->counter.num[6] = new_file_img("./textures/num/6.xpm", game);
	game->counter.num[7] = new_file_img("./textures/num/7.xpm", game);
	game->counter.num[8] = new_file_img("./textures/num/8.xpm", game);
	game->counter.num[9] = new_file_img("./textures/num/9.xpm", game);
	i = -1;
	while (++i < 10)
	{
		if (!game->counter.num[i].img)
			return (0);
	}
	return (1);
}

int	load_items_images(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->items_nb)
	{
		game->item[i].img = new_file_img("./textures/item.xpm", game);
		if (!game->item[i].img.img)
		{
		//	while (--i)
		//		mlx_destroy_image(game->mlx, game->item[i].img.img);
			return (0);
		}
	}
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
	{
		//free_image(game, game->counter.num, 10);
		return (0);
	}
	game->hero.face[0] = new_file_img("./textures/h1.xpm", game);
	game->hero.face[1] = new_file_img("./textures/h2.xpm", game);
	game->hero.face[2] = new_file_img("./textures/h3.xpm", game);
	game->hero.face[3] = new_file_img("./textures/h4.xpm", game);
	if (!game->hero.face[0].img || !game->hero.face[1].img
		|| !game->hero.face[2].img || !game->hero.face[3].img)
		return (0);
	game->map.ground = new_file_img("./textures/ground.xpm", game);
	if (!game->map.ground.img)
		return (0);
	game->map.wall = new_file_img("./textures/wall.xpm", game);
	if (!game->map.wall.img)
		return (0);
	return (1);
}
