#include "so_long.h"
int	check_pos(t_data *game, int x, int y)
{
	x = x / game->map.def;
	y = y / game->map.def;
	if (game->map.soil[y][x] == 1)
		return (0);
	else if (game->map.soil[y][x] == 0)
		return (1);
	return (0);
}

int	render(void *data)
{
	handle_input(data);
	draw_map(data);
	draw_hero(data);
	return (0);
}
void	draw_hero(t_data *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->hero.img, game->hero.pos_x, game->hero.pos_y);
}
/*void ft_put_pixel(t_data *game, int x, int y, int color)
{
    char *pxl;
    
    if (x >= 0 && x < game->width && y >= 0 && y < game->height)
    {
        pxl = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
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
*/

void	draw_map(t_data *game)
{
	int	i;
	int	x;
	int	y;
	char	*mapline;

	y = 0;
	game->map.fd = open("map.ber", O_RDONLY);
		while (y < game->height)
		{
			x = 0;
			i = 0;
			mapline = get_next_line(game->map.fd);
			while (x < game->width)
			{
				if (mapline[i] == '1')
					mlx_put_image_to_window(game->mlx, game->win, game->map.wall_tex, x, y);
				else
					mlx_put_image_to_window(game->mlx, game->win, game->map.ground_tex, x, y);
				i++;
				x += game->map.def;
			}
			free(mapline);
			y += game->map.def;
		}
		close(game->map.fd);
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
	
	height = -1;
	while (mapline)
	{
//		if (ft_strnlen(mapline, '\0') != width)
//		{
//			ft_printf("FAIL\n");
//			free(mapline);
//			return (0);
//		}
		ft_printf("%s    height = %d\n", mapline, height);
		height++;
		free(mapline);
		mapline = get_next_line(map->fd);
	}


	free(mapline);
	close(map->fd);
	map->height = height * def;
	map->width = width * def; 
	map->soil = malloc(sizeof(char*) * height);
	i = 0;
	while (i < height)
	{
		map->soil[i] = malloc (sizeof(char) * width);
		i++;
	}
	map->fd = open(path, O_RDONLY);
	mapline = get_next_line(map->fd);
	j = 0;
	while (j < height)
	{
		i = 0;
		while (i < width)
		{
			map->soil[j][i] = mapline[i];
			i++;
		}
		j++;
		free(mapline);
		mapline = get_next_line(map->fd);
	}
	free(mapline);

	map->def = def;
	return (1);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int	handle_no_event(void *data)
{
    /* This function needs to exist, but it is useless for the moment */
    return (0);
}

int handle_input(t_data *game)
{
    if (game->key_states[XK_Escape])
        close_window(game);
	if (game->key_states[KEY_W])
		move_up(game);
	if (game->key_states[KEY_A])
		move_left(game);
	if (game->key_states[KEY_S])
		move_down(game);
	if (game->key_states[KEY_D])
		move_right(game);
    return (0);
}

int key_press(int keycode, t_data *data) {
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 1; // Mark key as pressed
    return (0);
}

int key_release(int keycode, t_data *data) {
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 0; // Mark key as released
    return (0);
}

void	move_object(t_data *game)
{
	if (game->hero.pos_y < game->height - game->hero.height)
		game->hero.pos_y++;

}
void	move_down(t_data *game)
{
	if (game->hero.pos_y < game->height - game->hero.height && check_pos(game, game->hero.pos_x, game->hero.pos_y++))
		game->hero.pos_y++;
}
void	move_up(t_data *game)
{
	if (game->hero.pos_y > 0)
		game->hero.pos_y--;
}
void	move_right(t_data *game)
{
	if (game->hero.pos_x < game->width - game->hero.width)
		game->hero.pos_x++;
}
void	move_left(t_data *game)
{
	if (game->hero.pos_x > 0)
		game->hero.pos_x--;
}
