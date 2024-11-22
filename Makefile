NAME = so_long
LIBFT = libft/libft.a
SRCS = so_long.c rendering.c animation.c initialisation.c input.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -O0 -g
all : $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT) :
	make -C libft

clean	:
	make clean -C libft
	$(RM) $(OBJS)

fclean	: clean
	make fclean -C libft

re		: fclean all

.PHONY : all clean fclean re
