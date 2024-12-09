/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:26:25 by npolack           #+#    #+#             */
/*   Updated: 2024/12/09 13:29:52 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	anim(t_movable *perso)
{
	static int	delay;

	if (delay > ANIM_DELAY)
	{
		perso->frame = (perso->frame + 1) % 4;
		delay = 0;
	}
	delay++;
}
