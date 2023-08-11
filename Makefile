NAME	:= cub3d
CFLAGS	:= -Wextra -Wall #-Werror -Wunreachable-code -Ofast -g3
LIBMLX	:= ./MLX42
LIBFT 	:= libft/libft.a
LIBFT_PATH := libft/


HEADERS	:= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT_PATH)
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= main.c calc.c draw.c keys.c move.c read_map_file.c read_map.c read_textures_1.c read_textures_2.c map_check.c render.c error.c gnl1.c gnl2.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(LIBFT) $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(SRCS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

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

re: clean all

.PHONY: all, clean, fclean, re, libmlx