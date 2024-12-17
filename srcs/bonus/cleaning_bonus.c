/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:20:33 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 12:52:49 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	free_image(t_data *game, t_img *img, int i)
{
	while (--i >= 0)
	{
		if (img[i].img)
			mlx_destroy_image(game->mlx, img[i].img);
		img[i].img = NULL;
	}
	return (0);
}

int	init_to_zero(t_data *data)
{
	int	i;

	data->counter.moves = 0;
	i = -1;
	while (++i < 4)
		data->hero.face[i].img = NULL;
	i = -1;
	while (++i < 10)
		data->counter.num[i].img = NULL;
	data->item = NULL;
	data->map.ground.img = NULL;
	data->map.wall.img = NULL;
	data->exit.img.img = NULL;
	data->img.img = NULL;
	data->mlx = NULL;
	data->win = NULL;
	i = -1;
	while (++i < 99999)
		data->key_states[i] = 0;
	return (1);
}

int	destroy_items(t_data *game)
{
	int	i;

	i = 0;
	while (i < game->items_nb)
	{
		if (game->item[i].img.img)
		{
			mlx_destroy_image(game->mlx, game->item[i].img.img);
			game->item[i].img.img = NULL;
		}
		i++;
	}
	if (game->item)
		free(game->item);
	game->item = NULL;
	return (0);
}

int	free_all_images(t_data *game)
{
	free_image(game, game->counter.num, 10);
	destroy_items(game);
	free_image(game, game->hero.face, 4);
	if (game->map.ground.img)
		mlx_destroy_image(game->mlx, game->map.ground.img);
	if (game->map.wall.img)
		mlx_destroy_image(game->mlx, game->map.wall.img);
	if (game->exit.img.img)
		mlx_destroy_image(game->mlx, game->exit.img.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	return (0);
}

int	clean_all(t_data *data)
{
	free_all_images(data);
	free_mob(data, &data->mob);
	free_all(data->map.soil, data->map.h);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	return (0);
}
