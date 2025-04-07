NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = ./mlx
LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz
LIBFT = $(LIBFT_DIR)/libft.a

SRC = so_long.c map.c utils.c render.c movement.c validation.c flood_fill.c\
	  $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	  printf/ft_printf.c printf/ft_printf_func.c

OBJS = $(SRC:.c=.o)

INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
