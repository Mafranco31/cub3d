# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 15:02:38 by mafranco          #+#    #+#              #
#    Updated: 2024/06/29 15:35:19 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

LIB	=	include/cubed.h

LIBMLX_PATH	=	./mlx/
LIBFT_PATH	=	./libft/
LIBPF_PATH	=	./ftprintf/

LIBFT	=	libft.a
LIBPF	=	libftprintf.a
LIBMLX	=	libmlx.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT))
LIBPF_LIB	=	$(addprefix $(LIBPF_PATH), $(LIBPF))
LIBMLX_LIB	=	$(addprefix $(LIBMLX_PATH), $(LIBMLX))

SRC_DIR	=	src
SRC	=	$(wildcard $(SRC_DIR)/*.c)

MLX_FLAG	=	-lm -lX11 -lXext -L./mlx -lmlx

MLX_EX	=	$(MLX_LIB) $(MLX_FLAG)

CC	=	cc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -I.

OBJ	=	$(SRC:.c=.o)

GREEN	=	\033[1;32m
YELLOW	=	\033[1;33m
RESET	=	\033[0m


%.o:	%.c $(LIB)
	@$(CC) $(CFLAGS) -c $< -o $@

all:
	@make -C $(LIBMLX_PATH)
	@make -C $(LIBFT_PATH)
	@make -C $(LIBPF_PATH)
	@make $(NAME)

$(NAME): $(OBJ)

	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAG) $(LIBFT_LIB) $(LIBPF_LIB) -o $(NAME)
	@echo "$(GREEN)$(NAME) created$(RESET)"

clean:
	@$(RM) -r $(SRC_DIR)/*.o
	@echo "$(YELLOW)objects of $(NAME) removed$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(LIBMLX_PATH)
	@make clean -C $(LIBPF_PATH)
	@echo "$(YELLOW)$(NAME) removed$(RESET)"

re:	fclean all

.PHONY: all clean fclean re
