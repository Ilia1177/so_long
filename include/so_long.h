/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <npolack@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:13:10 by npolack           #+#    #+#             */
/*   Updated: 2024/12/07 17:00:33 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>
# include <X11/X.h>
# include "../libft/include/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define SPEED_MOB	5
# define SPEED_PLA	0

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_l;
	int		w;
	int		h;
}	t_img;

typedef struct s_count
{
	t_img	num[10];
	int		moves;
}	t_count;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_item
{
	int			exist;
	t_point		pos;
	int			height;
	int			width;
	t_img		img;
}	t_item;

typedef struct s_movable
{
	t_point				acc;
	t_point				vel;
	t_point				pos;
	unsigned int		moves;
	int					width;
	int					height;
	int					frame;
	t_img				face[4];
	struct s_movable	*next;
}	t_movable;

typedef struct s_map
{
	int		fd;
	int		def;
	int		w;
	int		h;
	char	**soil;
	t_img	wall;
	t_img	ground;
}	t_map;

typedef struct s_data
{
	t_count		counter;
	t_item		exit;
	t_item		*item;
	t_movable	hero;
	t_movable	*mob;
	void		*mlx;
	void		*win;
	t_map		map;
	t_map		flooded_map;
	t_img		img;
	int			def;
	int			items_nb;
	int			height;
	int			width;
	int			key_states[99999];
}	t_data;

//	image_utils.c //
unsigned int	get_pixel_img(t_img img, int x, int y);
t_img			new_img(int w, int h, t_data *game);
void			put_pixel_img(t_data *game, int x, int y, int color);
void			put_img_to_game(t_data *game, t_img src, int x, int y);
t_img			new_file_img(char *path, t_data *game);

//	flood_map.c
int				init_flooded_map(t_data *game);
int				flood_map(t_data *game, int i, int j);

//	map.c
int				measure_map(t_map *map, char *path);
int				map_cmp(t_data *game);
int				fill_soil(t_map *map);
int				make_soil(t_map *map, char *path);

//	utils.c
t_point			make_point(int x, int y);
double			dist(t_point a, t_point b);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data);
void			refresh(t_data *game);

//	check.c //
int				check_map(t_data *game);
int				check_pos(t_data *game, int x, int y);
void			check_items(t_data *game);
int				count_object(t_data *game, int object);
int				items_exist(t_data *game);

//	cleaning.c //
int				free_all(char **object, int i); //
int				close_window(t_data *data);
int				free_line(char *line);
void			destroy_counter(t_data *game);

//	rendering.c	//
int				render(void *data);
void			draw_exit(t_data *game);
void			draw_hero(t_data *game);
void			draw_collectable(t_data *game);
void			draw_map(t_data *game);

//	initialisation
int				init_hero(t_data *game);
int				init_map(t_data *game, char *path, int def);
int				game_init(t_data *game, char *path, int def);
int				init_collectable(t_data *game);
int				init_exit(t_data *game);

//	load_image
int				load_images(t_data *game);
int				load_items_images(t_data *game);
int				moves_on_screen(t_data *game);

//	input //
int				handle_input(t_data *data);
void			move_up(t_data *game);
void			move_down(t_data *game);
void			move_right(t_data *game);
void			move_left(t_data *game);

//	utils_bonus //
t_point			add_point(t_point a, t_point b);
int				ft_random(int min, int max);
t_point			multiply_point(t_point a, int x);

//	mob_bonus //
int				free_mob(t_data *game, t_movable **mob);
int				check_mob(t_data *game);
int				init_mob(t_data *game);
void			ft_mobadd_back(t_movable **lst, t_movable *new);
t_movable		*mk_mob(t_point pos);

//	mob2_bonus
void			draw_mob(t_data *game);
int				valid_objectpos(t_data *game, t_movable *obj, t_point pos);
void			move_mob(t_data *game);
int				ft_random(int min, int max);
#endif
