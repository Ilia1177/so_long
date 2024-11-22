/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:19:56 by npolack           #+#    #+#             */
/*   Updated: 2024/11/22 18:25:12 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

double	dist(t_point a, t_point b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

void	check_items(t_data *game)
{
	int	i;

	i = 0;
	ft_printf("%d, %d, %d\n", game->hero.pos.x, game->item[0].pos.x, game->map.def);
	while (i < game->items_nb)
	{
		if (dist(game->hero.pos, game->item[i].pos) < game->map.def)
			game->item[i].exist = 0;
		i++;
	}
}
 
int	check_pos(t_data *game, int x, int y)
{
	int i;
	int	j;

	i = x / game->map.def;
	j = y / game->map.def;
	if (x > game->width || y > game->height)
		return (0);
	if (x < 0 || y < 0)
		return (0);
	if (game->map.soil[j][i] == '1')
		return (0);
	else if (game->map.soil[j][i])
		return (1);
	return (0);
}

void	refresh(t_data *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
//	draw_map(game);
//	draw_collectable(game);
//	draw_hero(game);
}

int	render(void *data)
{
//  draw_map(data);
//	draw_hero(data);
	check_items(data);
	handle_input(data);
//	draw_collectable(data);
	return (0);
}
/*
unsigned int *copy_xpm_to_buffer(t_data *game, void *xpm_image, char *image_data)
{
    int x, y; // Iterators for looping through pixels
    unsigned int *buffer;

    // Step 1: Allocate memory for the buffer
    buffer = malloc(game->hero.width * game->hero.height * sizeof(unsigned int));
    if (!buffer) {
        perror("Error allocating buffer");
        exit(1); // Exit if memory allocation fails
    }
    // Step 2: Loop through every pixel in the image
    for (y = 0; y < game->hero.height; y++) {
        for (x = 0; x < game->hero.width; x++) {
            // Calculate the memory location of the current pixel in the image data
            char *pixel_addr = image_data + (y * game->hero.l_len + x * (game->hero.bpp / 8));

            // Read the pixel color and copy it into the buffer
            buffer[y * game->hero.width + x] = *(unsigned int *)pixel_addr;
        }
    }
    return buffer;
}*/

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

unsigned int	get_pixel_img(t_img img, int x, int y)
{
	return (*(unsigned int *)((img.addr + (y * img.line_l) + (x * img.bpp / 8))));
}

void	put_img_to_game(t_data *game, t_img src, int x, int y)
{
	int i;
	int j;
	unsigned int	color;

	i = 0;
	while(i < src.w)
   	{
		j = 0;
		while (j < src.h)
	   	{
			color = get_pixel_img(src, i, j);
	//		ft_printf("%x\n", color);
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
	t_img img;

	img.img = mlx_xpm_file_to_image(game->mlx, path, &img.w, &img.h);
	if (!img.img)
		write(2, "File could not be read\n", 23);
	else
		img.addr = mlx_get_data_addr(img.img, &(img.bpp), &(img.line_l), &(img.endian));
	return (img);
}

void	draw_hero(t_data *game)
{
	int		x;
	int		y;
	int		frame;
	t_img	img;
	void	*mlx;
	void	*win;
	void	*data;

	frame = game->hero.frame;
	x = game->hero.pos.x;
	y = game->hero.pos.y;
	img = game->hero.face[frame];
	win = game->win;
	mlx = game->mlx;
	put_img_to_game(game, img, x, y);
	//mlx_put_image_to_window(mlx, win, img, x, y);
}
void	draw_collectable(t_data *game)
{
	int	i;
	t_img	img;
	void	*mlx;
	void	*win;
	int		x;
	int		y;

	win = game->win;
	mlx = game->mlx;
	i = -1;
	while (++i < game->items_nb)
	{
		img = game->item[i].img;
		x = game->item[i].pos.x;
		y = game->item[i].pos.y;
		if (game->item[i].exist)
			put_img_to_game(game, img, x, y);
			//mlx_put_image_to_window(mlx, win, img, x, y);
	}
}

void	draw_map(t_data *game)
{
	t_point	pos;
	int		def;
	t_img	wa;
	t_img	gr;
	void	*win;
	void	*mlx;

	mlx = game->mlx;
	win = game->win;
	wa = game->map.wall;
	gr = game->map.ground;
	def = game->map.def;
	pos.y = -1;
	while (++pos.y < game->map.height / def)
	{
		pos.x = -1;
		while (++pos.x < game->map.width / def)
		{
			if (game->map.soil[pos.y][pos.x] == '1')
				put_img_to_game(game, wa, pos.x * def, pos.y * def);
			//	mlx_put_image_to_window(mlx, win, wa, pos.x * def, pos.y * def);
			else
				put_img_to_game(game, gr, pos.x * def, pos.y * def);
			//	mlx_put_image_to_window(mlx, win, gr, pos.x * def, pos.y * def);
		}
	}
}

int	make_map(t_map *map, char *path, int def)
{
	char	*mapline;
	int		width;
	int		height;
	int		i;
	int		j;

	map->fd = open(path, O_RDONLY);
	mapline = get_next_line(map->fd);
	width = ft_strnlen(mapline, '\n');
	height = 0;
	while (mapline && ft_strcmp(mapline, ""))
	{
		if (ft_strnlen(mapline, '\n') != width)
		{
			ft_printf("FAIL\n");
			free(mapline);
			return (0);
		}
		height++;
		free(mapline);
		mapline = get_next_line(map->fd);
	}
	free(mapline);
	close(map->fd);
	map->def = def;
	map->height = height * def;
	map->width = width * def; 
	map->soil = malloc(sizeof(char*) * height);
	map->fd = open(path, O_RDONLY);
	mapline = get_next_line(map->fd);
	j = -1;
	while (++j < height)
	{
		map->soil[j] = malloc(sizeof(char) * width);
		i = -1;
		while (++i < width)
			map->soil[j][i] = mapline[i];
		free(mapline);
		mapline = get_next_line(map->fd);
	}
	free(mapline);
	return (1);
}

int	close_window(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.height / data->map.def)
	{
		free(data->map.soil[i]);
		i++;
	}
	free(data->map.soil);
	mlx_destroy_image(data->mlx, data->hero.face[0].img);
	mlx_destroy_image(data->mlx, data->hero.face[1].img);
	mlx_destroy_image(data->mlx, data->hero.face[2].img);
	mlx_destroy_image(data->mlx, data->hero.face[3].img);
	mlx_destroy_image(data->mlx, data->map.ground.img);
	mlx_destroy_image(data->mlx, data->map.wall.img);
	i = -1;
	while (++i < data->items_nb)
		mlx_destroy_image(data->mlx, data->item[i].img.img);
	free(data->item);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}


