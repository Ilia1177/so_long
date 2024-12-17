/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:08:27 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 14:09:14 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_input(t_data *game)
{
	static int	count;

	if (game->key_states[XK_Escape])
		close_window(game);
	if (count > SPEED_PLA)
	{
		if (game->key_states[XK_w] || game->key_states[XK_Up])
			move_up(game);
		if (game->key_states[XK_a] || game->key_states[XK_Left])
			move_left(game);
		if (game->key_states[XK_s] || game->key_states[XK_Down])
			move_down(game);
		if (game->key_states[XK_d] || game->key_states[XK_Right])
			move_right(game);
		count = 0;
	}
	count++;
	return (0);
}

void	move_down(t_data *game)
{
	int	x;
	int	y;

	game->hero.frame = 0;
	x = game->hero.pos.x;
	y = game->hero.pos.y + game->hero.height + 1;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x + game->hero.width, y))
		return ;
	else
	{
		game->hero.pos.y += 1;
		game->count++;
		ft_printf("%d\n", game->count);
	}
}

void	move_up(t_data *game)
{
	int	x;
	int	y;

	game->hero.frame = 0;
	x = game->hero.pos.x;
	y = game->hero.pos.y - 1;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x + game->hero.width, y))
		return ;
	else
	{
		game->hero.pos.y -= 1;
		game->count++;
		ft_printf("%d\n", game->count);
	}
}

void	move_right(t_data *game)
{
	int	x;
	int	y;

	game->hero.frame = 0;
	x = game->hero.pos.x + game->hero.width + 1;
	y = game->hero.pos.y;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x, y + game->hero.height))
		return ;
	else
	{
		game->hero.pos.x += 1;
		game->count++;
		ft_printf("%d\n", game->count);
	}
}

void	move_left(t_data *game)
{
	int	x;
	int	y;

	game->hero.frame = 0;
	x = game->hero.pos.x - 1;
	y = game->hero.pos.y;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x, y + game->hero.height))
		return ;
	else
	{
		game->hero.pos.x -= 1;
		game->count++;
		ft_printf("%d\n", game->count);
	}
}
