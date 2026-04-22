##
## EPITECH PROJECT, 2024
## my makefile
## File description:
## makefile
##

NAME	=		libmy.a

SRCS	=		$(wildcard *.c)

OBJS	=		$(SRCS:.c=.o)

LIB		=		-L./libmy.a -I./include

LIB_CRI	=		--coverage -lcriterion

$(NAME)	:		$(OBJS)
				ar rc $(NAME) $(OBJS)
				mv $(NAME) ../

.PHONY	:		all clean fclean re unit_tests tests_run

all		:		$(NAME)

clean	:
				rm -f $(OBJS)

fclean	:		clean
				rm -f *.gcda *.gcno ../$(NAME)

re		:		fclean all

unit_tests	:	re
				gcc -o unit_tests $(SRCS) ../../tests/*.c \
				$(LIB) $(LIB_CRI)

tests_run	:	unit_tests
				./unit_tests
