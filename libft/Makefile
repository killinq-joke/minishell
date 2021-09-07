SRCS	= ft_strlen.c ft_atoi.c ft_bzero.c ft_calloc.c\
		ft_isalpha.c ft_isdigit.c\
		ft_isalnum.c ft_isascii.c ft_isprint.c ft_memccpy.c\
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memset.c\
		ft_memmove.c ft_strchr.c ft_strdup.c ft_strlcat.c\
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
		ft_strrchr.c ft_tolower.c ft_toupper.c\
		ft_strjoin.c ft_strtrim.c ft_substr.c ft_itoa.c\
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
		ft_putnbr_fd.c ft_split.c ft_putstr.c ft_putnbr.c ft_isin.c ft_atol.c\
		ft_sort_int_tab.c ft_intisin.c ft_superiorintisin.c ft_tabncpy.c ft_swap.c\
		ft_strcmp.c ft_atof.c ft_puterr.c ft_joinchar.c ft_putstrnl.c\
		ft_strisnum.c ft_spacecount.c\

OBJS		= ${SRCS:.c=.o}

BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c\
		  ft_lstiter.c ft_lstmap.c\

BONUS_OBJS	= ${BONUS:.c=.o}

NAME		= libft.a

CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	ar rcs ${NAME} ${OBJS}

all:		${NAME}

bonus:		${BONUS_OBJS}
	ar rcs ${NAME} ${BONUS_OBJS}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
	${RM} ${NAME}

re:		fclean all
