#include <mlx.h>
#include <X11/keysym.h>
#include <math.h>
#include "libft/srcs/include/libft.h"
#include <fcntl.h>

#define	WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400

typedef struct	s_map{
	int		fd_map;
	int		tex_width;
	int		tex_height;
	int		width;
	int		height;
	void	*wall_tex;
}				t_map;


typedef struct	s_data {

	void	*mlx;
	void	*win;

	void	*face;
	int		width;
	int		height;
	int		color;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	draw_map(t_map *map, t_data *game);
