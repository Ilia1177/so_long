/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:59:04 by npolack           #+#    #+#             */
/*   Updated: 2024/12/17 14:05:55 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	free_all(char **object, int i)
{
	while (--i >= 0)
		free(object[i]);
	free(object);
	return (0);
}

int	free_line(char *line)
{
	free(line);
	return (0);
}

int	close_window(t_data *data)
{
	clean_all(data);
	exit(0);
	return (0);
}
