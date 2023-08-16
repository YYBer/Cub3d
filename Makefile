NAME			:= cub3d
NAME_BONUS		:= cub3d_bonus
CFLAGS			:= -Wextra -Wall -Werror -Wunreachable-code -g3
# removed -Ofast due to errors
LIBMLX			:= ./MLX42
LIBFT 			:= libft/libft.a
LIBFT_PATH 		:= libft/

HEADERS			:= -I ./include -I $(LIBMLX)/include/MLX42 -I $(LIBFT_PATH)
LIBS			:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS_DIR		:= ./mandatory/
SRCS_BONUS_DIR	:= ./bonus/
SRCS			:= $(addprefix $(SRCS_DIR), main.c calc.c draw.c keys.c minimap.c move.c mouse.c read_color.c read_map_file.c read_map.c read_texture.c read_utils.c \
				map_check.c render.c error.c)
SRCS_BONUS		:= $(addprefix $(SRCS_BONUS_DIR), main.c calc.c draw.c keys.c minimap.c move.c mouse.c read_color.c read_map_file.c read_map.c read_texture.c read_utils.c \
				map_check.c render.c error.c)
OBJS			:= ${SRCS:.c=.o}
OBJS_BONUS		:= ${SRCS_BONUS:.c=.o}

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

bonus: libmlx $(NAME_BONUS) $(LIBFT)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	@$(CC) $(SRCS_BONUS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME_BONUS)

clean:
	@rm -rf $(OBJS) $(OBJS_BONUS)
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(LIBMLX)/build
	@echo "clean finished!"

fclean: clean
	@make fclean -sC $(LIBFT_PATH)
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "fclean finished!"

re: clean all

rebonus: fclean
				make bonus

.PHONY: all, clean, fclean, re, libmlx, rebonus