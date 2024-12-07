/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 16:10:07 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5 || ft_strcmp(path + (len - 4), ".ber"))
	{
		ft_printf("Map should be in '.ber' format!\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	game;

	game.counter.moves = 0;
	if (ac != 2)
		return (0);
	if (!check_path(av[1]))
		return (0);
	if (!game_init(&game, av[1], 50))
	{
		perror("init ");
		return (0);
	}
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 17, 1L << 2, close_window, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
}
