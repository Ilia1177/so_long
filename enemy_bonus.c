int	init_mob(t_data *game)
{
	int	i, j, random;
	t_movable	**mob;

	i = -1;	
	while (++i < game->map.h)
	{
		j = -1;
		while (++j < game->map.w)
		{
			if (game->map_>soil[j][i] == '0' && random < 5)
			{
				mob = malloc(sizeof(t_movable *));
				mob.pos = make_point(i * game->map.def, j * game->map.def);
			}
		}
	}
}

int	ft_random(int start, int max)
{
	int fd;
	int	i;
	int res;

	res = malloc(sizeof(int));
	fd = open(/dev/random);
	while (i < max)
	{
		read(1, res, O_RDONLY);
		i++;
	}
