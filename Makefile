NAME = ft_ls

SRC = Sources/directory.c Sources/flag_l.c Sources/flags.c Sources/ft.c Sources/main.c Sources/merge_sort.c Sources/print.c Sources/struct.c Sources/ft_strsplit.c Sources/ft_2.c Sources/t_sort.c

OBJ  = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

RED= \033[1;31m
GREEN= \033[1;32m
YELLOW= \033[1;33m
BLUE= \033[1;34m
VIOLET= \033[1;35m

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LIBFLAGS) -o $(NAME)
	@echo "$(GREEN)Project is successfully compiled"

%.o : %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED)Suspending library files$(VIOLET)"
	rm -rf *.o

fclean: clean
	@echo "$(RED)Suspending project files$(VIOLET)"
	rm -rf $(OBJ)
	rm -rf $(NAME)

re: fclean all
