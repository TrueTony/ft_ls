NAME = ft_ls

SRCS := add_func.c \
        checks.c \
        main.c \
        parse.c \
        sort.c

OBJ = $(SRCS:.c=.o)

LIB_DIR = ./printf/
LIBFT = $(LIB_DIR)libftprintf.a
LIB_HDR = $(LIB_DIR)src/libft/libft.h
FLAGS = -g -Wall -Werror -Wextra
INCLUDE = ./inc/ft_ls.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	gcc $(FLAGS) -c $<

$(NAME): $(OBJ)
	$(MAKE) -C $(LIB_DIR)
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L$(LIB_DIR) -I$(LIB_HDR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all