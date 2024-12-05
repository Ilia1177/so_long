/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob2_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:43:05 by npolack           #+#    #+#             */
/*   Updated: 2024/12/05 16:18:33 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_mob(t_data *game)
{
	t_movable	*move;

	move = game->mob;

	while (move)
	{
		put_img_to_game(game, move->face[0], move->pos.x, move->pos.y);
		move = move->next;
	}
}

int	valid_objectpos(t_data *game, t_movable *obj, t_point pos)
{
	int i1;
	int	j1;
	int i2;
	int j2;
	char **map;

	map = game->map.soil;
	i1 = pos.x / game->map.def;
	j1 = pos.y / game->map.def;
	i2 = (pos.x + obj->width) / game->map.def;
	j2 = (pos.y + obj->height) / game->map.def;
	if (pos.x >= game->width || pos.y >= game->height)
		return (0);
	if (pos.x < 0 || pos.y < 0)
		return (0);
	if (map[j1][i1] == '1' || map[j1][i2] == '1' 
		|| map[j2][i1] == '1' || map[j2][i2] == '1')
		return (0);
	else if (map[j1][i1] && map[j1][i2] && map[j2][i1] && map[j2][i2])
		return (1);
	return (0);
}

void	move_mob(t_data *game)
{
	t_movable	*mob;
	t_point		new_pos_x;
	t_point		new_pos_y;

	mob = game->mob;
	while (mob)
	{
		new_pos_x = add_point(mob->pos, make_point(mob->vel.x, 0));
		new_pos_y = add_point(mob->pos, make_point(0, mob->vel.y));
		if (valid_objectpos(game, mob, new_pos_x))
			mob->pos.x = new_pos_x.x;
		else
			mob->vel.x *= -1;
		if (valid_objectpos(game, mob, new_pos_y))
			mob->pos.y = new_pos_y.y;
		else 
			mob->vel.y *= -1;
		mob = mob->next;
	}
}
