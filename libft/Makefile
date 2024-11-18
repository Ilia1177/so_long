# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npolack <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:27:51 by npolack           #+#    #+#              #
#    Updated: 2024/10/30 12:53:48 by npolack          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

LIBFT		=	./srcs/libft.a

SRCS		=	./srcs/ft_printf/ft_printf.c\
				./srcs/ft_printf/ft_print_str.c\
				./srcs/ft_printf/ft_print_char.c\
				./srcs/ft_printf/ft_print_dec.c\
				./srcs/ft_printf/ft_print_hex.c\
				./srcs/ft_printf/ft_print_unsigned.c\
				./srcs/ft_printf/ft_putnb_base.c\
				./srcs/ft_printf/ft_print_address.c\
				./srcs/ft_printf/ft_parse.c\
				./srcs/ft_printf/get_intlen.c\
				./srcs/get_next_line/get_next_line_bonus.c\
				./srcs/get_next_line/get_next_line_utils_bonus.c

OBJS		=	$(SRCS:.c=.o)

AR 			=	ar -rcs

CC			=	cc 

CFLAGS		=	-Wall -Wextra -Werror -g

RM			=	rm -f

all				:	$(NAME) 

$(NAME)			:	$(OBJS) $(LIBFT)
					cp $(LIBFT) $(NAME)
					$(AR) $(NAME) $(OBJS)

$(LIBFT)	:
		make -C srcs

.c.o	 		:
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean	:	
			make clean -C srcs
			$(RM) $(OBJS)

fclean	:	clean
			make fclean -C srcs
			$(RM) $(NAME)

re		:	fclean all


.PHONY	:	all clean fclean re bonus
