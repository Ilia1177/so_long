/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:40:08 by npolack           #+#    #+#             */
/*   Updated: 2024/12/05 18:50:55 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_pixel_img(t_data *game, int x, int y, int color)
{
	char	*dst;
	t_img	*img;

	img = &game->img;
	if (x >= 0 && y >= 0 && x < game->width && y < game->height)
	{
		dst = img->addr + (y * img->line_l + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

t_img	new_img(int w, int h, t_data *game)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_l, &img.endian);
	img.w = w;
	img.h = h;
	return (img);
}

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	unsigned int	p;

	p = *(unsigned int *)((img.addr + (y * img.line_l) + (x * img.bpp / 8)));
	return (p);
}

void	put_img_to_game(t_data *game, t_img src, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	i = 0;
	while (i < src.w)
	{
		j = 0;
		while (j < src.h)
		{
			color = get_pixel_img(src, i, j);
			if (color == 0xFF000000)
			{
				j++;
				continue ;
			}
			put_pixel_img(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

t_img	new_file_img(char *path, t_data *game)
{
	t_img	i;

	i.img = mlx_xpm_file_to_image(game->mlx, path, &i.w, &i.h);
	if (!i.img)
		perror("new file img");
	else
		i.addr = mlx_get_data_addr(i.img, &i.bpp, &i.line_l, &i.endian);
	return (i);
}
