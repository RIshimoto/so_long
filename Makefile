NAME = so_long 
CC = gcc
CFLAGS = -I. -Wall -Wextra -Werror
LIB = libft/libft.a
SRCS =\
	./sources/so_long.c\
	./sources/berfile_check/fetch_game_data.c\
	./sources/berfile_check/fetch_each_line.c\
	./sources/berfile_check/check_map_char.c\
	./sources/berfile_check/check_map_closed.c\
	./sources/berfile_check/get_next_line.c
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) -L. -L./sources/libft $(OBJS) -lmlx -lft -I./include -lXext -lX11 -lm 

$(LIB):
	$(MAKE) -C ./sources/libft

all: $(NAME) $(LIB)

clean:
	rm -f ./sources/*.o
	rm -f ./sources/*/*.o
	$(MAKE) clean -C ./sources/libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./sources/libft

re: fclean all


.PHONY: all clean fclean re .c.o
