/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:11:35 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 16:07:55 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

t_point	add_point(t_point a, t_point b)
{
	t_point	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	return (res);
}

t_point	multiply_point(t_point a, int x)
{
	t_point	res;

	res.x = a.x * x;
	res.y = a.y * x;
	return (res);
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
	close(fd);
	range = max - min + 1;
	return ((random_value % range) + min);
}
