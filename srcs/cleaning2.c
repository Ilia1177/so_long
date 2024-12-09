/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:20:33 by npolack           #+#    #+#             */
/*   Updated: 2024/12/09 22:11:09 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_image(t_data *game, t_img *img, int i)
{
	while (i >= 0)
	{
		mlx_destroy_image(game->mlx, img[i].img);
		i--;
	}
	return (0);
}

int	free_win_n_display(t_data *game)
{
		free(game->item);
		free_all(game->map.soil, game->map.h);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
}

int	init_to_zero(t_data *data)
{
	int i;

	i = -1;
	while (++i < 4)
		data->hero.face[i].img = NULL;
	i = -1;
	while (++i < 10)
		data->counter.num[i].img = NULL;
	data->map.ground.img = NULL;
	data->map.wall.img = NULL;
	data->exit.img.img = NULL;
	data->img.img = NULL;
	data->mlx = NULL;
	data->win = NULL;
	return (1);
}
