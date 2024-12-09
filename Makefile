NAME = so_long
UNAME = $(shell uname)
SRCS_DIR = srcs
OBJS_DIR = objs
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
CLONE = mlx

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -lm -lz -framework OpenGL -framework AppKit
endif

LIBFT = libft/bin/libft.a

SRCS = 	anim.c\
		initialisation2.c\
		utils.c\
		load_image.c\
		check.c\
		cleaning.c\
		cleaning2.c\
		so_long.c\
		rendering.c\
		initialisation.c\
		input.c\
		image_utils.c\
		map.c\
		flood_map.c\
		mob_bonus.c\
		mob2_bonus.c\
		utils_bonus.c\
		counter_bonus.c\

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

CFLAGS = -Wall -Wextra -Werror -g -O0
CC = cc

all : $(MLX_LIB) $(NAME) $(LIBFT)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME) 

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) -c $< -o $@ -I$(MLX_DIR) $(INCLUDES)

$(MLX_LIB): $(CLONE) 
		make -C $(MLX_DIR)

$(CLONE) : 
	git clone https://github.com/42Paris/minilibx-linux.git $(CLONE)

$(LIBFT) : 
	make -C libft

clean	:
	make clean -C libft
	make clean -C $(MLX_DIR)
	rm -fr $(OBJS_DIR)

fclean	: clean
	make fclean -C libft
	rm -fr $(MLX_DIR)
	rm $(NAME)

re		: fclean all

.PHONY : all clean fclean re
