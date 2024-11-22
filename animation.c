#include "so_long.h"

void	animate(t_data *game)
{
	static int	counter;

//	mlx_clear_window(game->mlx, game->win);

    mlx_put_image_to_window(game->mlx, game->win, game->hero.face[game->hero.frame].img, game->hero.pos.x, game->hero.pos.y);
	counter++;
    if (counter >= 5) { // Assuming ~10ms per loop iteration
        counter = 0;
        game->hero.frame = (game->hero.frame + 1) % 4; // Cycle through 0-3
    }
}
