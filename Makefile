# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ztouzri <ztouzri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/02 09:47:58 by ztouzri           #+#    #+#              #
#    Updated: 2021/09/16 13:51:38 by ztouzri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
LIB		= libft.a
SRCS	= 	main.c parspipe.c parspipe2.c checkerror.c utils.c env.c \
			exec.c execbuiltins.c execbuiltins2.c execbuiltins3.c execbuiltins4.c exec_command_non_pipe.c all_execution_non_pipe.c \
			all_execution_pipe.c builtins_pipe.c slash_command_non_pipe.c builtins_non_pipe.c builtins_non_pipe2.c\
			exec_command_pipe.c slash_command_pipe.c pipe.c parsline.c redir.c clean.c commandsplit.c \
			exec_command_pipe2.c exec_command_non_pipe2.c signal.c parsline2.c parsline3.c execbuiltins5.c\
			ft_trimquotes.c pipe2.c utils1.c
OBJS	= $(SRCS:c=o)

.c.o:
	$(CC) $(CFLAGS) -c $< -Ilibft

.PHONY: all clean fclean re
all:	$(NAME)

$(NAME):	$(OBJS)
	make -C libft
	mv libft/$(LIB) .
	$(CC) $(CFLAGS) $(OBJS) $(LIB)  -lreadline ./includes/libreadline.a -lcurses -o $(NAME)

clean:
	$(RM) $(OBJS) $(LIB) file*

fclean: clean
	$(RM) $(NAME)

re:		fclean all