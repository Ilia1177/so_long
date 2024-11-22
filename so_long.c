/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:15:52 by npolack           #+#    #+#             */
/*   Updated: 2024/11/22 18:29:43 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(void)
{
	t_data	game;
	
	if (!make_map(&game.map, "map.ber", 50))
		return (0);
	game_init(&game);


	draw_map(&game);
	refresh(&game);	
// register event
	//mlx_loop_hook(game.mlx, &render, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);    // Key press event
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);	 // Key release event

//	loop execute
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
    free(game.mlx);
}
