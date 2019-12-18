# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wkorande <wkorande@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:58:13 by wkorande          #+#    #+#              #
#    Updated: 2019/12/18 22:13:50 by wkorande         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CFLAGS = -Wall -Wextra -Werror

SRCS = fractol.c\
		controls.c\
		frame_buffer.c\
		mandelbrot.c\
		julia.c\
		point.c\
		color.c

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

libft:
	make re -C $(LIBFT)

linux:
	gcc $(FLAGS) -o $(NAME) -I$(INCL) -I $(LIBFT)/includes $(SRC) -L$(LIBFT) -lft -lmlx -lXext -lX11 -lm

clean:
	@printf "Removing objects\n"
	@rm -f $(OBJ)

fclean : clean
	@printf "Removing $(NAME)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all libft clean fclean re
