NAME	= philo

SRCS 	= src/main.c src/philosophers.c src/philosophers_functions.c src/philosophers_utils.c

OBJS 	= ${SRCS:.c=.o}

HEADER	= -Iinclude

CC 	= gcc
CFLAGS 	= -Wall -Wextra -Werror

.c.o:		
					$(CC) ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all:		${NAME}

${NAME}:	${OBJS}
					$(CC) ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

clean:
					rm -f ${OBJS}

fclean: 	clean
					@rm -f ${NAME}

re:			fclean all

.PHONY: 	all clean fclean re
