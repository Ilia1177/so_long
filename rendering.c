#include "so_long.h"

void	draw_map(t_map *map, t_data *game)
{
	int	i;
	int	x;
	int	y;
	char	*mapline;

	i = 0;
	y = 0;
//	map->fd_map = open("map.ber", O_RDONLY);
		while (y < WINDOW_HEIGHT)
		{
			x = 0;
//			mapline = get_next_line(map->fd_map);
			while (x < WINDOW_WIDTH)
			{
//				if (mapline[i] == '1')
					mlx_put_image_to_window(game->mlx, game->win, map->wall_tex, x, y);
				i++;
				x += map->tex_width;
			}
			y += map->tex_height;
		}
}
