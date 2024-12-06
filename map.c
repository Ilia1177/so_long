/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:40:18 by npolack           #+#    #+#             */
/*   Updated: 2024/12/06 19:09:12 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	init_flooded_map(t_data *game)
{
	int	w;
	int	h;
	int	i;
	int	j;

	w = game->map.w;
	h = game->map.h;
	game->flooded_map.h = h;
	game->flooded_map.w = w;
	game->flooded_map.soil = malloc(sizeof(char *) * h);
	if (!game->flooded_map.soil)
		return (0);
	j = -1;
	while (++j < h)
	{
		game->flooded_map.soil[j] = malloc(sizeof (char) * w);
		if (!game->flooded_map.soil[j])
			return (free_all(game->flooded_map.soil, j));
		i = -1;
		while (++i < w)
			game->flooded_map.soil[j][i] = '0';
	}
	return (1);
}

int	map_cmp(t_data *game)
{
	int		i;
	int		j;
	char	c;

	j = -1;
	while (++j < game->map.h)
	{
		i = -1;
		while (++i < game->map.w)
		{
			c = game->map.soil[j][i];
			if (c != 'E' && c != 'P' && c != '1' && c != '0' && c != 'C')
				return (0);
			if (c == 'E')
				if (game->flooded_map.soil[j][i] != 'V')
					return (0);
			if (c == 'C')
				if (game->flooded_map.soil[j][i] != 'V')
					return (0);
			if (j == 0 || j == game->map.h -1 || i == 0 || i == game->map.w -1)
				if (c != '1')
					return (0);
		}
	}
	return (1);
}

int	flood_map(t_data *game, int i, int j)
{
	int		h;
	int		w;

	w = game->map.w;
	h = game->map.h;
	if (j < 0 || j >= h)
		return (0);
	else if (i < 0 || i >= w)
		return (0);
	else if (game->map.soil[j][i] == '1')
		return (0);
	else if (game->flooded_map.soil[j][i] == 'V')
		return (0);
	else
	{
		game->flooded_map.soil[j][i] = 'V';
		flood_map(game, i + 1, j);
		flood_map(game, i, j + 1);
		flood_map(game, i - 1, j);
		flood_map(game, i, j - 1);
	}
	return (1);
}

int	measure_map(t_map *map, char *map_name)
{
	char	*mapline;
	char	*path;

	path = ft_strjoin("./maps/", map_name);
	if (!path)
		return (0);
	map->fd = open(path, O_RDONLY);
	free(path);
	mapline = get_next_line(map->fd);
	if (!mapline)
		return (0);
	map->w = ft_strnlen(mapline, '\n');
	map->h = 0;
	while (mapline)
	{
		if (ft_strnlen(mapline, '\n') != map->w)
			return (free_line(mapline));
		map->h++;
		free(mapline);
		mapline = get_next_line(map->fd);
	}
	free(mapline);
	close(map->fd);
	return (1);
}

int	fill_soil(t_map *map)
{
	char	*mapline;
	int		i;
	int		j;

	mapline = get_next_line(map->fd);
	j = -1;
	while (++j < map->h)
	{
		map->soil[j] = malloc(sizeof(char) * map->w);
		if (!map->soil[j])
			return (free_all(map->soil, j));
		i = -1;
		while (++i < map->w)
			map->soil[j][i] = mapline[i];
		free(mapline);
		mapline = get_next_line(map->fd);
	}
	free(mapline);
	return (1);
}

int	make_soil(t_map *map, char *map_name)
{
	char	*mapline;
	int		i;
	int		j;
	char	*path;

	path = ft_strjoin("./maps/", map_name);
	if (!path)
		return (0);
	map->fd = open(path, O_RDONLY);
	free(path);
	map->soil = malloc(sizeof (char *) * map->h);
	if (!map->soil)
		return (0);
	if (!fill_soil(map))
		return (0);
	close(map->fd);
	return (1);
}
