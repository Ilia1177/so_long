#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "libft/srcs/include/libft.h"
#include <fcntl.h>
#include <stdio.h>

#define KEY_W			119
#define KEY_A			97
#define KEY_S			115
#define KEY_D			100
#define KEY_ESC 		65307
#define KEY_Q 			113
#define KEY_R 			114
#define KEY_LEFT_ARROW		65361
#define KEY_UP_ARROW		65362
#define KEY_RIGHT_ARROW		65363
#define KEY_DOWN_ARROW		65364

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		endian;
	int		line_l;
	int		w;
	int		h;
}				t_img;

typedef struct	s_point {
	int	x;
	int	y;
}				t_point;

typedef struct	s_item {
	int		exist;
	t_point	pos;
	int		height;
	int		width;
	t_img	img;
}				t_item;

typedef struct	s_movable {
	int		endian;
	t_point	pos;
	int		width;
	int		height;
	int		frame;
	t_img	face[4];
}				t_movable;

typedef struct	s_map{
	int		fd;
	int		def;
	int		w;
	int		h;
	char	**soil;
	t_img	wall;
	t_img	ground;
}				t_map;

typedef struct	s_data {

	t_item		exit;
	t_item		*item;
	t_movable	hero;
	t_movable	*enemy;
	void		*mlx;
	void		*win;
	t_map		map;
	t_map		flooded_map;
	t_img		img;
	int			def;
	int			items_nb;
	int			height;
	int			width;
	int     	key_states[99999];
}				t_data;

void			draw_circle(t_data *game, int x, int y, int size, int color);
void			draw_hero(t_data *game);
void			draw_map(t_data *game);
int				render(void *data);
void			ft_put_pixel(t_data *data, int x, int y, int color);
int				close_window(t_data *data);
int				handle_no_event(void *data);
int				handle_input(t_data *data);
int				make_map(t_map *map, char *path, int def);
void			move_up(t_data *game);
void			move_down(t_data *game);
void			move_right(t_data *game);
void			move_left(t_data *game);
int				key_press(int keycode, t_data *data);
int				key_release(int keycode, t_data *data); 
void			animate(t_data *game);
void			draw_collectable(t_data *game);
int				init_hero(t_data *game);
int				game_init(t_data *game, char *path, int def);
int				init_map(t_data *game, char *path, int def);
int				init_collectable(t_data *game);
int				free_items(t_data *game, int i);
int				count_collectable(t_data *game);

int				check_pos(t_data *game, int x, int y);

t_img			new_img(int w, int h, t_data *game);
t_img			new_file_img(char * path, t_data *game);
void			put_img_to_game(t_data *game, t_img src, int x, int y);
void			put_pixel_img(t_data *game, int x, int y, int color);
unsigned int	get_pixel_img(t_img img, int x, int y);
void			refresh(t_data *game);
int				init_exit(t_data *game);
void			draw_exit(t_data *game);
int				flood_map(t_data *game, int i, int j);
int				check_map(t_data *game);
int				free_all(char **object, int i);
int				make_soil(t_map *map, char *path);
int				load_images(t_data *game);
t_point			make_point(int x, int y);
