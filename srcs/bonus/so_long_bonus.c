/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 12:56:34 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strcmp(path + (len - 4), ".ber"))
	{
		ft_printf("Error\nMap should be in '.ber' format!\n");
		return (0);
	}
	return (1);
}

int	mlx_hook_n_loop(t_data *game)
{
	mlx_loop_hook(game->mlx, &render, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 2, close_window, game);
	mlx_loop(game->mlx);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	game;
	int		ready;

	init_to_zero(&game);
	if (ac != 2)
		return (0);
	if (!check_path(av[1]))
		return (0);
	ready = init_map(&game, av[1], 50);
	if (ready == -1)
	{
		ft_printf("Error\nMap is invalid!\n");
		return (0);
	}
	else if (ready == 1)
	{
		if (game_init(&game))
			mlx_hook_n_loop(&game);
		else
			perror("Error\n");
	}
	else
		perror("init ");
	return (0);
}
