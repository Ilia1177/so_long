#include "so_long.h"

int	close_window(int keycode, t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	return (0);
}

int	handle_no_event(void *data)
{
    /* This function needs to exist, but it is useless for the moment */
    return (0);
}

int	handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        close_window(keysym, data);
    return (0);
}



int	main(void)
{
	t_data	game;
	t_map	map;
	
	int def = 50;

	int map_height;
	int map_width;

	if (!make_map(&map, "map.ber", def))
		return (0);

	WINDOW_HEIGHT = def * map_height;
	WINDOW_WIDTH = def * map_width;
	map.tex_width = def * map_width;
	map.tex_height = def;


	char	*relative_path = "./image/ground.xpm";
//	int offset = (y * line_length + x * (bits_per_pixel / 8));

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello world!");

	game.img = mlx_new_image(game.mlx, WINDOW_HEIGHT, WINDOW_WIDTH);
	game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);

// read image
	map.wall_tex = mlx_xpm_file_to_image(game.mlx, relative_path, &map.tex_width, &map.tex_height);

// register event
	mlx_loop_hook(game.mlx, &handle_no_event, &game);
	mlx_loop_hook(game.mlx, &render, &game);
    mlx_key_hook(game.win, &handle_input, &game);

//	put image on windows
	draw_map(&map, &game);
//	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	draw_circle(&game, 50, 50, 10, 0xFFEEAABB);
draw_circle(&game, 50, 50, 11, 0xFFEEAABB);
	draw_circle(&game, 50, 50, 12, 0xFFEEAABB);
	draw_circle(&game, 50, 50, 13, 0xFFEEAABB);
	draw_circle(&game, 50, 50, 14, 0xFFEEAABB);

//	loop execute
	mlx_loop(game.mlx);
}
