#include "so_long.h"

int	check_pos(t_data *game, int x, int y)
{
	int i;
	int	j;

	i = x / game->map.def;
	j = y / game->map.def;
	if (x >= game->width || y >= game->height)
		return (0);
	if (x <= 0 || y <= 0)
		return (0);
	if (game->map.soil[j][i] == '1')
		return (0);
	else if (game->map.soil[j][i])
		return (1);
	return (0);
}

int	render(void *data)
{
	handle_input(data);
	draw_map(data);
	draw_hero(data);
	draw_collectable(data);
//	animate(data);
	return (0);
}
#include <stdlib.h>
#include <stdio.h>

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
}

void	draw_hero(t_data *game)
{
	void	*buffer;
	char	*data;

//	buffer = mlx_new_image(game->mlx, game->hero.width, game->hero.height);
	data = mlx_get_data_addr(game->hero.img, &game->hero.bpp, &game->hero.l_len, &game->hero.endian);
	buffer = copy_xpm_to_buffer(game, game->hero.img, data);

//	mlx_put_image_to_window(game->mlx, game->win, buffer, 0, 0);
mlx_put_image_to_window(game->mlx, game->win, game->hero.sprite[game->hero.current_frame], game->hero.pos_x, game->hero.pos_y);
}

void	draw_collectable(t_data *game)
{
	int	i;

	i = -1;
	while (++i < game->items_nb)
		if (game->item[i].exist)
			mlx_put_image_to_window(game->mlx, game->win, game->item[i].img, game->item[i].x, game->item[i].y);
}

void	draw_map(t_data *game)
{
	int	i;
	int	x;
	int	y;
	char	*mapline;

	y = 0;
	game->map.fd = open("map.ber", O_RDONLY);
		while (y < game->map.height)
		{
			x = 0;
			i = 0;
			mapline = get_next_line(game->map.fd);
			while (x < game->map.width)
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
	int	y;

	y = 0;
	while (y < data->map.height / data->map.def)
	{
		free(data->map.soil[y]);
		y++;
	}
	free(data->map.soil);
	free(data->hero.sprite[0]);
	free(data->hero.sprite[1]);
	free(data->hero.sprite[2]);
	free(data->hero.sprite[3]);
	free(data->map.ground_tex);
	free(data->map.wall_tex);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	exit(0);
	return (0);
}

/*int	handle_no_event(void *data)
{
    return (0);
}*/

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

int key_press(int keycode, t_data *data)
{
    if (keycode >= 0 && keycode < 99999)
        data->key_states[keycode] = 1; // Mark key as pressed
    return (0);
}

int key_release(int keycode, t_data *data)
{
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
	int x;
	int	y;

    game->hero.current_frame = (game->hero.current_frame + 1) % 4; // Cycle through 0-3
	x = game->hero.pos_x;
	y = game->hero.pos_y + 1 + game->hero.height;
	if (check_pos(game, x, y))
		game->hero.pos_y++;
}

void	move_up(t_data *game)
{
	int x;
	int	y;

    game->hero.current_frame = (game->hero.current_frame + 1) % 4; // Cycle through 0-3
	x = game->hero.pos_x;
	y = game->hero.pos_y - 1;
	if (check_pos(game, x, y))
		game->hero.pos_y--;
}

void	move_right(t_data *game)
{
	int	x;
	int	y;

    game->hero.current_frame = (game->hero.current_frame + 1) % 4; // Cycle through 0-3
	x = game->hero.pos_x + game->hero.width + 1;
	y = game->hero.pos_y;
	if (check_pos(game, x, y))
		game->hero.pos_x++;
}

void	move_left(t_data *game)
{
	int	x;
	int	y;

    game->hero.current_frame = (game->hero.current_frame + 1) % 4; // Cycle through 0-3
	x = game->hero.pos_x - 1;
	y = game->hero.pos_y;
	if (check_pos(game, x, y))
		game->hero.pos_x--;
}
