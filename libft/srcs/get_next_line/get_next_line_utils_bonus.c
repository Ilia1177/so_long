/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:43:12 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 12:44:51 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line_bonus.h"

int	ft_strnlen(const char *str, int c)
{
	char	*start;

	start = (char *)str;
	while (*str && *str != c)
		str++;
	return (str - start);
}
