NAME = so_long
LIBFT = libft/libft.a
SRCS = so_long.c rendering.c
OBJS = $(SRCS:.c=.o)
all : $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(LIBFT) :
	make -C libft

clean	:
	make clean -C libft
	$(RM) $(OBJS)

fclean	: clean
	make fclean

re		: fclean all

.PHONY : all clean fclean re
