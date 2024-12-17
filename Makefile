NAME = so_long
B_NAME = so_long_bonus

UNAME = $(shell uname)
SRCS_DIR = srcs
OBJS_DIR = objs
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
CLONE = mlx

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm 
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -lm -framework OpenGL -framework AppKit
endif

LIBFT = libft/bin/libft.a

SRCS = 	initialisation2.c\
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
		flood_map.c

B_SRCS =	anim_bonus.c\
			mob_bonus.c\
			mob2_bonus.c\
			utils_bonus.c\
			counter_bonus.c\
			rendering_bonus.c\
			initialisation2_bonus.c\
			utils2_bonus.c\
			load_image_bonus.c\
			check_bonus.c\
			cleaning2_bonus.c\
			cleaning_bonus.c\
			so_long_bonus.c\
			initialisation_bonus.c\
			input_bonus.c\
			image_utils_bonus.c\
			map_bonus.c\
			flood_map_bonus.c


SRCS := $(addprefix $(SRCS_DIR)/mandatory/, $(SRCS))
B_SRCS := $(addprefix $(SRCS_DIR)/bonus/, $(B_SRCS))

OBJS = $(SRCS:$(SRCS_DIR)/mandatory/%.c=$(OBJS_DIR)/mandatory/%.o)
B_OBJS = $(B_SRCS:$(SRCS_DIR)/bonus/%.c=$(OBJS_DIR)/bonus/%.o)

CFLAGS = -Wall -Wextra -Werror

CC = cc

all :  $(LIBFT) $(MLX_LIB) $(NAME)

bonus : $(LIBFT) $(MLX_LIB) $(B_NAME)

$(NAME): $(OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(NAME) -L./libft/bin -lft

$(B_NAME): $(B_OBJS)
	$(CC) $^ $(MLX_FLAGS) -o $(B_NAME) -L./libft/bin -lft

$(OBJS_DIR)/mandatory/%.o: $(SRCS_DIR)/mandatory/%.c
	mkdir -p $(OBJS_DIR)/mandatory
	$(CC) $(CFLAGS) -c $< -o $@ -I$(MLX_DIR) $(INCLUDES)

$(OBJS_DIR)/bonus/%.o: $(SRCS_DIR)/bonus/%.c
	mkdir -p $(OBJS_DIR)/bonus
	$(CC) $(CFLAGS) -c $< -o $@ -I$(MLX_DIR) $(INCLUDES)

$(MLX_LIB): $(CLONE) 
		make -C $(MLX_DIR)

$(CLONE) : 
	git clone https://github.com/42Paris/minilibx-linux.git $(CLONE)

$(LIBFT) : 
	make -C libft

clean	:
	-make clean -C libft
	-make clean -C $(MLX_DIR)
	-rm -fr $(OBJS_DIR)
	-rm -fr $(B_OBJS_DIR)

fclean	: clean
	-make fclean -C libft
	rm -fr $(MLX_DIR)
	-rm $(NAME)
	-rm $(B_NAME)

re		: fclean all

.PHONY : all clean fclean re bonus
