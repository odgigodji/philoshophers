NAME		=	philosophers

SRC			=	ft_atoi.c phils.c monitoring.c initialization.c

HEADER		=	phils.h

OBJ			=	$(SRC:.c=.o)

CC			=	gcc -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ) $(LFT_DIR)/$(LFT) Makefile
			$(CC) -o $@ $(OBJ)

%.o	:		%.c $(HEADER)

clean:
			-rm -f $(OBJ)

fclean:		clean
			make clean
			-rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
