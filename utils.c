/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:53:41 by npolack           #+#    #+#             */
/*   Updated: 2024/12/04 13:55:57 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_point	make_point(int x, int y)
{
	t_point	point;

	point.x = x;
	point.y = y;

	return (point);
}

double	dist(t_point a, t_point b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int key_press(int keycode, t_data *data)
{
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
	data->hero.frame = 0;
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 0;
    return (0);
}



