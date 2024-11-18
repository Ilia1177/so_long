#include "so_long.h"

int	render(void *data)
{
	//ft_put_pixel(data, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFFFF );
	ft_printf("RENDER\n");
	return (0);
}

void ft_put_pixel(t_data *data, int x, int y, int color)
{
    char *pxl;
    
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        pxl = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int *)pxl = color;
    }
}
void	draw_circle(t_data *game, int x, int y, int size, int color)
{
	int angle;
	angle = 0;
	while (angle < 360)
	{
		ft_put_pixel(game, x + (cos(angle) * size),  y + (sin(angle) * size), color);
		angle++;
	}
}

void	draw_map(t_map *map, t_data *game)
{
	int	i;
	int	x;
	int	y;
	char	*mapline;

	i = 0;
	y = 0;
	map->fd_map = open("map.ber", O_RDONLY);
		while (y < WINDOW_HEIGHT)
		{
			x = 0;
			mapline = get_next_line(map->fd_map);
			while (x < WINDOW_WIDTH)
			{
				if (mapline[i] == '1')
					mlx_put_image_to_window(game->mlx, game->win, map->wall_tex, x, y);
				i++;
				x += map->tex_width;
			}
			free(mapline);
			y += map->tex_height;
		}
}

int	make_map(t_map *map, char *path, int def)
{
	t_map	*map;
	char	*mapline;
	int		width;
	int		height;
	int		fd;

	map->fd_map = open(*path);
	mapline = get_next_line(fd);
	width = ft_strnlen(mapline, "\n");
	while (mapline)
	{
		if (ft_strnlen(mapline, "\n") != width)
		{
			free(mapline);
			return (0);
		}
		height++;
		free(mapline);
		mapline = get_next_line
	}
	free(mapline);
	map->height = height;
	map->width = width; 
	map->def = def;
}
