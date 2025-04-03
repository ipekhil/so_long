# === Project Name ===
NAME = so_long

# === Compiler Settings ===
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# === Directories ===
MLX_DIR = ./mlx
LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line

# === Libraries ===
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
LIBFT = $(LIBFT_DIR)/libft.a

# === Source Files ===
SRC = so_long.c map.c utils.c render.c movement.c validation.c flood_fill.c\
	  $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	  printf/ft_printf.c printf/ft_printf_func.c

# === Object Files ===
OBJS = $(SRC:.c=.o)

# === Includes ===
INCLUDES = -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR)

# === Default Rule ===
all: $(NAME)

# === Link and Build ===
$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

# === Compile .c → .o ===
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# === Clean ===
clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
