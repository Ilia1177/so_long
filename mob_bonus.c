/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mob_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 10:50:48 by npolack           #+#    #+#             */
/*   Updated: 2024/11/27 12:52:16 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_mob(t_data *game)
{
	int	i, j, random;
	t_movable	*new;

	i = -1;	
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			random = ft_random(0, 100);
			if (game->map.soil[j][i] == '0' && random < 20)
			{
				new = make_mob(make_point(i * game->map.def, j * game->map.def));
				new->face[0] = new_file_img("image/face.xpm", game);
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

t_point	wander(t_point current_pos, int max_dist)
{
	// Seed random number generator
    static int seeded = 0;
    t_point new_pos;

    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    // Generate random angle in radians
    int angle = (int)(rand() % 360) * (3.14159f / 180.0f);

    // Generate random step size (up to max_distance)
    int distance = (int)rand() / RAND_MAX * max_dist;

    // Calculate new position
    new_pos.x = current_pos.x + distance * cos(angle);
    new_pos.y = current_pos.y + distance * sin(angle);
    return new_pos;
}

void	move_mob(t_data *game)
{
	t_movable	*mob;

	mob = game->mob;

	while (mob)
	{
		mob->pos = wander(mob->pos, 5);
		mob = mob->next;
	}
}

int	ft_random(int min, int max)
{
	int				fd;
	int				i;
	int				n;
	unsigned int	random_value;

	fd = open("/dev/random", O_RDONLY);
	if (fd <= 0)
		return (0);
	n = read(fd, &random_value, sizeof(random_value));

    int range = max - min + 1;
    return (random_value % range) + min;
}
