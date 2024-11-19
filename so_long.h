#include <mlx.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include "libft/srcs/include/libft.h"
#include <fcntl.h>

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

//#define	WINDOW_WIDTH 400
//#define WINDOW_HEIGHT 400


typedef struct	s_movable {
	int		pos_y;
	int		pos_x;
	int		width;
	int		height;
	void	*img;
	char	*addr;
	
}				t_movable;

typedef struct	s_map{
	int		fd;
	int		def;
	int		width;
	int		height;
	char	**soil;
	void	*wall_tex;
	void	*ground_tex;
}				t_map;

typedef struct	s_data {

	int		def;
	t_movable	hero;
	t_movable	*enemy;
	void	*mlx;
	void	*win;
	t_map	map;
	int		width;
	int		height;
//	void	*img;
//	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int     key_states[99999];
}				t_data;


void	draw_circle(t_data *game, int x, int y, int size, int color);
void	draw_hero(t_data *game);
void	draw_map(t_data *game);
int		render(void *data);
void	ft_put_pixel(t_data *data, int x, int y, int color);
int		close_window(t_data *data);
int		handle_no_event(void *data);
int		handle_input(t_data *data);
int		make_map(t_map *map, char *path, int def);
void	move_up(t_data *game);
void	move_down(t_data *game);
void	move_right(t_data *game);
void	move_left(t_data *game);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data); 
