/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:27:40 by npolack           #+#    #+#             */
/*   Updated: 2024/10/16 19:04:41 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	sign = 1;
	result = 0;
	while (*nptr)
	{
		while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
			nptr++;
		if (*nptr == '-')
		{
			sign *= -1;
			nptr++;
		}
		else if (*nptr == '+')
			nptr++;
		while (*nptr >= '0' && *nptr <= '9')
		{
			result = result * 10 + (*nptr) - '0';
			nptr++;
		}
		return (result * sign);
	}
	return (0);
}
