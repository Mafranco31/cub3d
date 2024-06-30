# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/27 13:06:34 by mafranco          #+#    #+#              #
#    Updated: 2024/06/29 15:36:35 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a

LIB = ft_printf.h

SRC	=	ft_printf.c ft_pfptr.c ft_pfchar.c ft_pfint.c

CC	=	cc

CFLAGS	=	-Werror -Wall -Wextra -I.

RM	=	rm -f

OBJ = $(SRC:.c=.o)

GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
RESET	=	\033[0m

all:	$(NAME)

%.o: %.c $(LIB)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)ftprintf.a compiled$(RESET)"

clean:
	@$(RM) -r *.o
	@echo "$(YELLOW)objects of ftprintf removed$(RESET)"

fclean: clean
	@$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
