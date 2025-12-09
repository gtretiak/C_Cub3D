# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/09 09:55:06 by rimagalh          #+#    #+#              #
#    Updated: 2025/12/09 10:41:26 by rimagalh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

SRC = draw.c \
	keys.c \
	move.c \
	raycast.c\
	render.c\
	texture.c\
	utils.c\
	memory/free.c \
	memory/init.c \
	memory/player.c \


OBJ = $(SRC:.c=.o)

LIBFT_DIR = ../../lib/libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = ../../lib/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(MLX) -L$(MLX_DIR) -lmlx -L/usr/X11/lib -lXext -lX11 -lm

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

gdb: CFLAGS += -g

gdb: re

re: fclean all

.PHONY: all clean fclean gdb re
