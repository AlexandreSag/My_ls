CC = gcc
NAME = my_ls
SRC = main.c \
	  my_tools.c \
	  my_ls.c \
	  wich_option.c \
	  recursive.c \
	  stats_ls.c
RM = rm -f
OBJ = $(SRC:%.c=%.o)
CFLAGS = -Wall -Werror -Wextra
$(NAME):	$(OBJ)
	$(CC) $(OBJ) -o $(NAME)
all:	$(NAME)
clean:
	$(RM) $(OBJ)
fclean:	clean
	$(RM) $(NAME)
re:	fclean all