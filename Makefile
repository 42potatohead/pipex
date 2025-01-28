NAME = pipex
SRC = pipex.c pipex_utilities.c exit.c
LIBFT_DIR = ./libft

OBJ := $(SRC:%.c=%.o)

CC = cc
CCFLAGS = -Wextra -Wall -Werror -L./libft -lft -g

all: $(NAME)

$(NAME): $(OBJ) libft
	$(CC) $(OBJ) $(CCFLAGS) -o $(NAME)

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	make clean
	rm -f $(NAME)

re : fclean all clean

.PHONY : all clean fclean libft
