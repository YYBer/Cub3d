NAME	:= cub3d
CFLAGS	:= -g3 -Wextra -Wall -Werror #-Wunreachable-code # -Ofast
CC		:= cc
LIBMLX	:= ./MLX42
LIBFT 	:= libft/libft.a
LIBFT_PATH := libft/

HEADERS	:= -I./include -I$(LIBMLX)/include/MLX42 -I$(LIBFT_PATH)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS_DIR:= ./src/
SRCS 	:= $(addprefix $(SRCS_DIR), calc.c draw.c error_free1.c error_free2.c keys.c main.c map_check.c minimap.c move.c \
			print.c read_color.c read_map1.c read_map2.c read_map_file.c read_texture.c read_utils.c \
				render.c rotate.c)
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(LIBFT) $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	@echo "Compiling $(NAME)..."
	@$(CC) $(SRCS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)
	@echo "$(NAME) compiled!"

$(LIBFT):
	@echo "Compiling libft..."
	@make -sC $(LIBFT_PATH)
	@echo "libft compiled!"

clean:
	@rm -rf $(OBJS)
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(LIBMLX)/build
	@echo "clean finished!"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -rf $(NAME)
	@echo "fclean finished!"

re: fclean all

.PHONY: all, clean, fclean, re, libmlx