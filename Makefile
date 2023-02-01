SRCS    = 	main_philo.c\
			philo_utils.c\
			philo_time.c\
			philo_init.c\
			philo_check_death.c\
			philo.routine.c\
			philo.thread.c\
			philo_destroy.c

DIR_SRC_PHILO = ./sources/srcs_philo/
OBJ	= ${SRCS:.c=.o}
DIR_OBJ = sources/objs/
OBJS = $(addprefix $(DIR_OBJ), $(OBJ))
DEP = ${SRCS:.c=.d}
DEPS = $(addprefix $(DIR_OBJ), $(DEP))
NAME = philo

HEADERS	= -I includes
CC		= gcc -pthread -g
CFLAGS	= -MMD -Wall -Wextra -Werror

${NAME} : ${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all :		${NAME}

clean:
			rm -f ${OBJS} ${DEPS}

fclean:		clean
			rm -f philo

re:			fclean all

$(DIR_OBJ)%.o: $(DIR_SRC_PHILO)%.c 
	${CC} ${CFLAGS} -c $< ${HEADERS} -o $@

-include ${DEPS}

.PHONY: all clean fclean re