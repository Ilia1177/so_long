NAME = so_long
UNAME = $(shell uname)
MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -lm -lz -framework OpenGL -framework AppKit
endif
CLONE = mlx
LIBFT = libft/libft.a
SRCS = so_long.c rendering.c initialisation.c input.c image_utils.c map.c mob_bonus.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -O0 -g
CC = cc

all : $(MLX_LIB) $(NAME) $(LIBFT)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME) 

%.o: %.c
	$(CC) -c $< -o $@ -I$(MLX_DIR) $(INCLUDES)

$(MLX_LIB): $(CLONE) 
		make -C $(MLX_DIR)

$(CLONE) : 
	git clone https://github.com/42Paris/minilibx-linux.git mlx

$(LIBFT) : 
	make -C libft

clean	:
	make clean -C libft
	$(RM) $(OBJS)

fclean	: clean
	rm $(NAME)
	make clean -C $(MLX_DIR)
	make fclean -C libft

re		: fclean all

.PHONY : all clean fclean re
