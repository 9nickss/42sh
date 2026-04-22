##
## EPITECH PROJECT, 2024
## my makefile
## File description:
## makefile
##

NAME		=		42sh

SRCS		=		$(wildcard src/*.c) \
  					$(wildcard src/**/*.c)

OBJS		=		$(SRCS:.c=.o)

LIB			=		-L./lib -lmylist -lmy -I./include

LIB_CRI		=		--coverage -lcriterion

VAL			=		--leak-check=full --track-origins=yes --show-leak-kinds=all

CFLAGS		+=		-Wall -Wextra -Wshadow -I./include

$(NAME)		:		$(OBJS)
					make -C lib/my/
					make -C lib/mylist/
					gcc -o $(NAME) $(OBJS) $(LIB)

.PHONY		:		all clean fclean re unit_tests tests_run val_run val run

all			:
					$(MAKE) $(NAME)

clean		:
					make clean -C lib/my/
					make clean -C lib/mylist/
					rm -f $(OBJS)

fclean		:		clean
					make fclean -C lib/my/
					make fclean -C lib/mylist/
					rm -f unit_tests
					rm -f *.gcda *.gcno *~ $(NAME)

re			:		fclean all

LIB_CRI 	= 		--coverage -lcriterion

unit_tests	:		fclean all
					gcc -o unit_tests $(SRCS) tests/*.c \
					$(LIB) $(LIB_CRI)

tests_run	:		unit_tests
					./unit_tests

val			:		re
					gcc -o $(NAME) $(SRCS) $(LIB) -g3

val_run			:	val
					@valgrind $(VAL) ./$(NAME)

run			:		re
					./$(NAME)
