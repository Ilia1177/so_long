/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:00:20 by npolack           #+#    #+#             */
/*   Updated: 2024/12/06 11:28:07 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	moves_on_screen(t_data *game)
{
	char	*num;
	int		i;

	num = ft_itoa(game->counter.moves);
	i = 0;
	while (num[i])
	{
		if (num[i] == '1')
			put_img_to_game(game, game->counter.num[1], i * 50, 0);
		if (num[i] == '2')
			put_img_to_game(game, game->counter.num[2], i * 50, 0);
		if (num[i] == '3')
			put_img_to_game(game, game->counter.num[3], i * 50, 0);
		if (num[i] == '4')
			put_img_to_game(game, game->counter.num[4], i * 50, 0);
		if (num[i] == '5')
			put_img_to_game(game, game->counter.num[5], i * 50, 0);
		if (num[i] == '6')
			put_img_to_game(game, game->counter.num[6], i * 50, 0);
		if (num[i] == '7')
			put_img_to_game(game, game->counter.num[7], i * 50, 0);
		if (num[i] == '8')
			put_img_to_game(game, game->counter.num[8], i * 50, 0);
		if (num[i] == '9')
			put_img_to_game(game, game->counter.num[9], i * 50, 0);
		if (num[i] == '0')
			put_img_to_game(game, game->counter.num[0], i * 50, 0);
		i++;
	}
	free(num);
	return (0);
}

/*unsigned int	display_moves(void)
{
	static unsigned int	moves;

	moves++;
	ft_printf("%u\n", moves);
	
	return (moves);
}*/

