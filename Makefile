NAME = so_long

SRC = so_long.c map.c utils.c render.c movement.c validation.c flood_fill.c \
	  get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	  printf/ft_printf.c printf/ft_printf_func.c

OBJS = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Imlx -Ilibft -Iget_next_line -Iprintf

MLX_FLAGS = -Lmlx -lmlx -lXext -lX11 -lm -lz
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
