/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:17:17 by npolack           #+#    #+#             */
/*   Updated: 2024/12/05 17:26:16 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
