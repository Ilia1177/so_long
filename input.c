/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:08:27 by npolack           #+#    #+#             */
/*   Updated: 2024/11/22 18:20:54 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int handle_input(t_data *game)
{
    if (game->key_states[XK_Escape])
        close_window(game);
	if (game->key_states[KEY_W])
		move_up(game);
	if (game->key_states[KEY_A])
		move_left(game);
	if (game->key_states[KEY_S])
		move_down(game);
	if (game->key_states[KEY_D])
		move_right(game);
    return (0);
}

int key_press(int keycode, t_data *data)
{
	//refresh(data);
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
	data->hero.frame = 0;
//	refresh(data);
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 0;
    return (0);
}

void	move_down(t_data *game)
{
	int x;
	int	y;

    game->hero.frame = (game->hero.frame + 1) % 4;
//	refresh(game);
	x = game->hero.pos.x;
	y = game->hero.pos.y + game->hero.height + 5; 
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x + game->hero.width, y))
		return ;
	else
		game->hero.pos.y += 5;
	//refresh(game);
}

void	move_up(t_data *game)
{
	int x;
	int	y;

    game->hero.frame = (game->hero.frame + 1) % 4;
	//refresh(game);
	x = game->hero.pos.x;
	y = game->hero.pos.y - 5;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x + game->hero.width, y))
		return ;
	else
		game->hero.pos.y -= 5;
	//refresh(game);
}

void	move_right(t_data *game)
{
	int	x;
	int	y;

    game->hero.frame = (game->hero.frame + 1) % 4;
	//refresh(game);
	x = game->hero.pos.x + game->hero.width + 5;
	y = game->hero.pos.y;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x, y + game->hero.height))
		return ;
	else
		game->hero.pos.x += 5;
	//refresh(game);
}

void	move_left(t_data *game)
{
	int	x;
	int	y;

    game->hero.frame = (game->hero.frame + 1) % 4;
	//refresh(game);
	x = game->hero.pos.x - 5;
	y = game->hero.pos.y;
	if (!check_pos(game, x, y))
		return ;
	if (!check_pos(game, x, y + game->hero.height))
		return ;
	else
		game->hero.pos.x -= 5;
	//refresh(game);
}
