#include "so_long.h"

void	animate(t_data *game)
{
	static int	counter;

//	mlx_clear_window(game->mlx, game->win);

    mlx_put_image_to_window(game->mlx, game->win, game->hero.sprite[game->hero.current_frame], game->hero.pos_x, game->hero.pos_y);
	counter++;
    if (counter >= 5) { // Assuming ~10ms per loop iteration
        counter = 0;
        game->hero.current_frame = (game->hero.current_frame + 1) % 4; // Cycle through 0-3
    }
}
