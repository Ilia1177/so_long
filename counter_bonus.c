/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:00:20 by npolack           #+#    #+#             */
/*   Updated: 2024/12/06 18:53:55 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	select_img(t_data *game, char c, int x)
{
	if (c == '1')
		put_img_to_game(game, game->counter.num[1], x * 50, 0);
	if (c == '2')
		put_img_to_game(game, game->counter.num[2], x * 50, 0);
	if (c == '3')
		put_img_to_game(game, game->counter.num[3], x * 50, 0);
	if (c == '4')
		put_img_to_game(game, game->counter.num[4], x * 50, 0);
	if (c == '5')
		put_img_to_game(game, game->counter.num[5], x * 50, 0);
	if (c == '6')
		put_img_to_game(game, game->counter.num[6], x * 50, 0);
	if (c == '7')
		put_img_to_game(game, game->counter.num[7], x * 50, 0);
	if (c == '8')
		put_img_to_game(game, game->counter.num[8], x * 50, 0);
	if (c == '9')
		put_img_to_game(game, game->counter.num[9], x * 50, 0);
	if (c == '0')
		put_img_to_game(game, game->counter.num[0], x * 50, 0);
}

int	moves_on_screen(t_data *game)
{
	char	*num;
	int		i;

	num = ft_itoa(game->counter.moves);
	i = 0;
	while (num[i])
	{
		select_img(game, num[i], i);
		i++;
	}
	free(num);
	return (0);
}
