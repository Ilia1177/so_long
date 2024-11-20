#include "so_long.h"

int	init_collectable(t_data *game)
{
	int	i;
	int	j;
	int	k;

	game->items_nb = 0;
	while (j < game->height / game->map.def)
	{
		i = 0;
		while (i < game->width / game->map.def)
		{
			if (game->map.soil[j][i] == 'C')
				game->items_nb++;
			i++;
		}
		j++;
	}
	game->item = (t_item *)malloc(sizeof(t_item) * game->items_nb);
	i = -1;
	while (++i < game->items_nb)
	{
		game->item[i].exist = 1;
		game->item[i].width = 50;
		game->item[i].height = 50;
		game->item[i].img = mlx_xpm_file_to_image(game->mlx, "./image/item.xpm", &game->item[i].width, &game->item[i].height); 
	}
	k = 0;
	j = 0;
	while (j < game->height / game->map.def)
	{
		i = 0;
		while (i < game->width / game->map.def)
		{
			if (game->map.soil[j][i] == 'C')
			{
				game->item[k].exist = 1;
				game->item[k].width = 50;
				game->item[k].height = 50;
				game->item[k].img = mlx_xpm_file_to_image(game->mlx, "./image/item.xpm", &game->item[k].width, &game->item[k].height); 
				game->item[k].x = i * game->map.def;
				game->item[k].y = j * game->map.def;
				k++;
			}
			i++;
		}
		j++;
	}
}

int	game_init(t_data *game)
{	
	int i;
	int j;

	game->height = game->map.height;
	game->width = game->map.width;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "HAZARDOU$ GAME");

	game->map.ground_tex = mlx_xpm_file_to_image(game->mlx, "./image/ground.xpm", &game->map.def, &game->map.def);
	game->map.wall_tex = mlx_xpm_file_to_image(game->mlx, "./image/wall.xpm", &game->map.def, &game->map.def);
	game->hero.img = mlx_xpm_file_to_image(game->mlx, "./image/hero_face.xpm", &game->hero.width, &game->hero.height);
	game->hero.sprite[0] = mlx_xpm_file_to_image(game->mlx, "./image/sprite1.xpm", &game->hero.width, &game->hero.height); 
	game->hero.sprite[1] = mlx_xpm_file_to_image(game->mlx, "./image/sprite2.xpm",&game->hero.width, &game->hero.height);
	game->hero.sprite[2] = mlx_xpm_file_to_image(game->mlx, "./image/sprite3.xpm",&game->hero.width, &game->hero.height);
	game->hero.sprite[3] = mlx_xpm_file_to_image(game->mlx, "./image/sprite4.xpm",&game->hero.width, &game->hero.height);
	game->hero.current_frame = 0;
	init_collectable(game);
	i = -1;
    while (++i < 99999)
		game->key_states[i] = 0;
	j = 0;
	while (j < game->height / game->map.def)
	{
		i = 0;
		while (i < game->width / game->map.def)
		{
			if (game->map.soil[j][i] == 'P')
			{
				game->hero.pos_x = i * game->map.def;
				game->hero.pos_y = j * game->map.def;
				break ;
			}
			i++;
		}
		j++;
	}
	return (1);
}

int	main(void)
{
	t_data	game;
	
	if (!make_map(&game.map, "map.ber", 50))
		return (0);
	game_init(&game);
//	draw_collectable(&game);
//	draw_map(&game);
// register event
	mlx_loop_hook(game.mlx, &render, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);    // Key press event
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);	 // Key release event

//	loop execute
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
    free(game.mlx);
}
