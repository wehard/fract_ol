# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/12/17 12:56:28 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

SRCS = fractol.c\
		frame_buffer.c\
		mandelbrot.c\
		julia.c\
		point.c

SRCDIR = .

SRC = $(addprefix $(SRCDIR)/, $(SRCS))

OUT = $(SRCS:.c=.o)

INCL = include

LIBFT=../libft

FLAGS= #-Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -lmlx -lm -framework OpenGL -framework AppKit

clean:
	@printf "Removing objects\n"
	@rm -f $(OBJ)

fclean : clean
	@printf "Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
