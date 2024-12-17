/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:59:04 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 12:52:34 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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
		if (game->counter.num[i].img)
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
	clean_all(data);
	exit(0);
	return (0);
}
