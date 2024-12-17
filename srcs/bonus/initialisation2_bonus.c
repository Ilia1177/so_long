/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:03:06 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 12:54:25 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	init_mlx(t_data *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free(game->item);
		free_all(game->map.soil, game->map.h);
		return (0);
	}
	return (1);
}

int	init_win(t_data *game)
{
	game->win = mlx_new_window(game->mlx, game->width, game->height, "HZD$");
	if (!game->win)
	{
		free(game->item);
		free_all(game->map.soil, game->map.h);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	return (1);
}

int	init_game_img(t_data *game)
{
	game->img = new_img(game->width, game->height, game);
	if (!game->img.img)
	{
		free(game->item);
		free_all(game->map.soil, game->map.h);
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (0);
	}
	return (1);
}
