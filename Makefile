NAME = cub3D
HEADER = cub3d.h
CUB_LIB = cub3D.a
CFLAGS = cc -Wall -Wextra -Werror
MLX_FLAGS = -lX11 -lXext -lXrender -lXrandr -lm -lpthread
LIBFT = libft.a
LIBFT_DIR = C_libft/
MLX = libmlx_Linux.a
MLX_DIR = minilibx_linux/
SRC_DIR = Sources/
SRC = main.c init.c events.c render.c utils.c 
OBJ = $(addprefix $(SRC_DIR), $(SRC:.c=.o))

all: $(LIBFT) $(MLX) $(CUB_LIB) $(NAME)

$(LIBFT):
	@if [ -d $(LIBFT_DIR) ]; then \
		echo "C_libft is already cloned."; \
	else \
		git clone git@github.com:gtretiak/C_libft.git $(LIBFT_DIR); \
	fi
	@if [ -f $(LIBFT_DIR)$(LIBFT) ]; then \
		echo "libft.a is already compiled."; \
	else \
		$(MAKE) -C $(LIBFT_DIR); \
	fi

$(MLX):
	@if [ -d $(MLX_DIR) ]; then \
		echo "minilibx_linux is already cloned."; \
	else \
		git clone git@github.com:42paris/minilibx-linux.git $(MLX_DIR); \
	fi
	@if [ -f $(MLX_DIR)$(MLX) ]; then \
		echo "libmlx_Linux.a is already compiled."; \
	else \
		$(MAKE) -C $(MLX_DIR); \
	fi

$(CUB_LIB): $(OBJ)
	ar -rcs $(CUB_LIB) $(OBJ)

$(SRC_DIR)%.o: $(SRC_DIR)%.c $(HEADER) $(MLX_DIR)$(MLX) $(LIBFT_DIR)$(LIBFT)
	$(CFLAGS) -I. -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(NAME): $(CUB_LIB) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX)
	@if [ ! -f $(NAME) ] || [ $(CUB_LIB) -nt $(NAME) ] || [ $(LIBFT) -nt $(NAME) ]; then \
		cc $(CUB_LIB) -L$(LIBFT_DIR) -lft $(MLX_DIR)$(MLX) $(MLX_FLAGS) -o $(NAME); fi


.PHONY: clean fclean re

clean:
	rm -f $(OBJ)
	@if [ -d $(LIBFT_DIR) ]; then make clean -C $(LIBFT_DIR); fi
	@if [ -d $(MLX_DIR) ]; then make clean -C $(MLX_DIR); fi

fclean: clean
	@if [ -f $(CUB_LIB) ]; then rm -f $(CUB_LIB); fi
	@if [ -f $(NAME) ]; then rm -f $(NAME); fi
	@if [ -d $(LIBFT_DIR) ]; then make fclean -C $(LIBFT_DIR); fi
	@if [ -d $(LIBFT_DIR) ]; then rm -rf $(LIBFT_DIR); fi
	@if [ -d $(MLX_DIR) ]; then rm -rf $(MLX_DIR); fi

re: fclean all
