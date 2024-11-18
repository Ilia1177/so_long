#include "so_long.h"


/*int	close(int keycode, t_map *map)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}
*/

int	handle_no_event(void *data)
{
    /* This function needs to exist, but it is useless for the moment */
    return (0);
}

int	handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx, data->win);
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

int	render(void *data)
{
	ft_put_pixel(data, WINDOW_WIDTH, WINDOW_HEIGHT, 0x00FFFFFF );
	ft_printf("RENDER\n");
	return (0);
}

int	main(void)
{
	t_data	game;
	t_map	map;
	
	map.tex_width = 50;
	map.tex_height = 50;

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


	int i = 0;
	int j = 0;
	int angle = 0;
	int color = 0x00ABCD;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
		//	angle = 0;
		//	while (angle < 360)
		//	{
			ft_put_pixel(&game, j, i, color);
		//		angle++;
		//i/	}
			i ++;
		}
		j++;
	}
//	draw_map(&map, &game);
	
//	mlx_put_image_to_window(game.mlx, game.win, map.wall_tex, 0, 0);
//	mlx_put_image_to_window(game.mlx, game.win, map.wall_tex, 0, 0);
//	make and put image on windows
	//game.color = 0x00FF0000;
	mlx_loop(game.mlx);
}
