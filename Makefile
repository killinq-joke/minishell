# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/02 09:47:58 by ztouzri           #+#    #+#              #
#    Updated: 2021/08/13 00:48:05 by ztouzri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g -fsanitize=address
LIB		= libft.a

SRCS	= main.c parspipe.c checkerror.c utils.c env.c exec.c execbuiltins.c
OBJS	= $(SRCS:c=o)

.c.o:
	$(CC) $(CFLAGS) -c $< -Ilibft

.PHONY: all clean fclean re
all:	$(NAME)

$(NAME):	$(OBJS)
	make -C libft
	mv libft/$(LIB) .
	$(CC) $(CFLAGS) $(OBJS) $(LIB)  -lreadline -o $(NAME)

clean:
	$(RM) $(OBJS) $(LIB)

fclean: clean
	$(RM) $(NAME)

re:		fclean all
