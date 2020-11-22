NAME = ft_ls

SRCS := add_func.c \
        checks.c \
        main.c \
        parse.c \
		prints.c \
        sort.c

OBJ = $(SRCS:.c=.o)

LIB_DIR = ./printf/
LIBFT = $(LIB_DIR)libftprintf.a

FLAGS = -Wall -Werror -Wextra
INCLUDE = ./inc/ft_ls.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	gcc $(FLAGS) -c $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LIBFT)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
