#include "so_long.h"




int	main(void)
{
	t_data	game;
	
	if (!make_map(&game.map, "map.ber", 50))
		return (0);

	game.height = game.map.height;
	game.width = game.map.width;
	
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, game.width, game.height, "Hello world!");
    for (int i = 0; i < 99999; i++) // Initialize key states
        game.key_states[i] = 0;

   // mlx_hook(data.win, 2, 1L << 0, key_press, &data);    // Key press event
   // mlx_hook(data.win, 3, 1L << 1, key_release, &data);

	//game.hero.width = 50;
	//game.hero.height = 50;
	game.hero.pos_x = 100;
	game.hero.pos_y = 100;
//	game.img = mlx_new_image(game.mlx, game.width, game.height);
//	game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &game.line_length, &game.endian);

// read image
	game.map.ground_tex = mlx_xpm_file_to_image(game.mlx, "./image/ground.xpm", &game.map.def, &game.map.def);
	game.map.wall_tex = mlx_xpm_file_to_image(game.mlx, "./image/wall.xpm", &game.map.def, &game.map.def);
	game.hero.img = mlx_xpm_file_to_image(game.mlx, "./image/hero_face.xpm", &game.hero.width, &game.hero.height);
	game.hero.addr = mlx_get_data_addr(game.hero.img, &game.bits_per_pixel, &game.line_length, &game.endian);

// register event
//	mlx_loop_hook(game.mlx, &handle_no_event, &game);
//	mlx_key_hook(game.win, handle_input, &game);
//  mlx_hook(game.win, KeyPress, KeyPressMask, &handle_input, &game);
//    mlx_hook(game.win, KeyPress, KeyPressMask, &handle_input, &game);
	mlx_loop_hook(game.mlx, &render, &game);
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);    // Key press event
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);	// Key release event
//	put image on windows
//	draw_circle(&game, 50, 50, 10, 0xFFEEAABB);
//	draw_circle(&game, 50, 50, 11, 0xFFEEAABB);
//	draw_circle(&game, 50, 50, 12, 0xFFEEAABB);
//	draw_circle(&game, 50, 50, 13, 0xFFEEAABB);
//	draw_circle(&game, 50, 50, 14, 0xFFEEAABB);
//	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);


//	loop execute
	mlx_loop(game.mlx);
}
