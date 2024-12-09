/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:59:04 by npolack           #+#    #+#             */
/*   Updated: 2024/12/09 16:35:03 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_all(char **object, int i)
{
	while (--i >= 0)
		free(object[i]);
	free(object);
	return (0);
}

void	destroy_counter(t_data *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		mlx_destroy_image(game->mlx, game->counter.num[i].img);
		i++;
	}
}

int	free_line(char *line)
{
	free(line);
	return (0);
}

int	close_window(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->hero.face[i].img);
	destroy_counter(data);
	mlx_destroy_image(data->mlx, data->map.ground.img);
	mlx_destroy_image(data->mlx, data->map.wall.img);
	mlx_destroy_image(data->mlx, data->exit.img.img);
	free_mob(data, &data->mob);
	free_all(data->map.soil, data->map.h);
	i = -1;
	while (++i < data->items_nb)
		mlx_destroy_image(data->mlx, data->item[i].img.img);
	free(data->item);
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}
