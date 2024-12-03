/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/12/03 12:18:24 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_data	game;

	if (ac != 2)
		return (0);
	if(!game_init(&game, av[1], 50))
	{
		perror("init ");
		return (0);
	}
	mlx_loop_hook(game.mlx, &render, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);    // Key press event
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);	 // Key release event
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
    free(game.mlx);
}
