/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:50:48 by npolack           #+#    #+#             */
/*   Updated: 2024/12/03 17:47:47 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int free_mob(t_data *game, t_movable **mob)
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

int check_mob(t_data *game)
{
	t_movable *mob;

	mob = game->mob;
	while (mob)
	{
		if (dist(mob->pos, game->hero.pos) < 20)
			close_window(game);
		mob = mob->next;
	}
	return (1);
}

int	init_mob(t_data *game)
{
	int	i, j, random;
	t_movable	*new;
	
	game->mob = 0;
	i = -1;	
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			random = ft_random(0, 100);
			if (game->map.soil[j][i] == '0' && random < 10)
			{
				new = make_mob(make_point(i * game->map.def, j * game->map.def));
				new->height= 20;
				new->width = 20;
				new->face[0] = new_file_img("image/mob.xpm", game);
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

t_movable	*make_mob(t_point pos)
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

t_point	add_point(t_point a, t_point b)
{
	t_point res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
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

t_point	multiply_point(t_point a, int x)
{
	t_point	res;

	res.x = a.x * x;
	res.y = a.y * x;
	return (res);
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

int	ft_random(int min, int max)
{
	int				fd;
	int				i;
	int				n;
	int				range;
	unsigned int	random_value;

	fd = open("/dev/random", O_RDONLY);
	if (fd <= 0)
		return (0);
	n = read(fd, &random_value, sizeof(random_value));

    range = max - min + 1;
    return (random_value % range) + min;
}

