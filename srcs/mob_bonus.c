/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:50:48 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 15:55:54 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_mob(t_data *game, t_movable **mob)
{
	t_movable	*tmp;

	while (*mob)
	{
		tmp = (*mob)->next;
		mlx_destroy_image(game->mlx, (*mob)->face[0].img);
		free(*mob);
		*mob = tmp;
	}
	*mob = NULL;
	return (0);
}

int	check_mob(t_data *game)
{
	t_movable	*mob;
	t_movable	*hero;
	t_point		hero_pos;
	t_point		mob_pos;
	int			dist_min;

	if (!game->mob)
		return (0);
	mob = game->mob;
	hero = &game->hero;
	dist_min = (game->hero.width / 2) + (mob->width / 2);
	hero_pos.x = hero->pos.x + hero->width / 2;
	hero_pos.y = hero->pos.y + hero->height / 2;
	while (mob)
	{
		mob_pos.x = mob->pos.x + mob->width / 2;
		mob_pos.y = mob->pos.y + mob->height / 2;
		if (dist(mob_pos, hero_pos) < dist_min)
			close_window(game);
		mob = mob->next;
	}
	return (1);
}

int	init_mob(t_data *game)
{
	int			i;
	int			j;
	t_movable	*new;

	game->mob = 0;
	i = -1;
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			if (game->map.soil[j][i] == '0' && ft_random(0, 100) < 5)
			{
				new = mk_mob(make_point(i * game->map.def, j * game->map.def));
				new->height = 20;
				new->width = 20;
				new->face[0] = new_file_img("textures/mob.xpm", game);
				if (!new->face[0].img)
					return (0);
				ft_mobadd_back(&game->mob, new);
			}
		}
	}
	return (1);
}

void	ft_mobadd_back(t_movable **lst, t_movable *new)
{
	t_movable	*move;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		move = *lst;
		while (move->next)
			move = move->next;
		move->next = new;
	}
}

t_movable	*mk_mob(t_point pos)
{
	t_movable	*mob;

	mob = malloc(sizeof(t_movable));
	if (!mob)
		return (0);
	mob->pos = pos;
	mob->next = NULL;
	mob->vel = make_point(ft_random(-2, 2), ft_random(-2, 2));
	return (mob);
}
