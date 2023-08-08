NAME = libftprintf.a

$(NAME): bonus

all: $(NAME)

clean:
	make -C ./libft clean
	rm -f ft_printf_bonus.o ft_printf_bonus_conversions1.o ft_printf_bonus_conversions2.o ft_printf_bonus_flags1.o ft_printf_bonus_flags2.o ft_printf_bonus_utils.o ft_printf_bonus_uitoa.o

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

bonus:
	make -C ./libft
	cc -Wall -Wextra -Werror -c ft_printf_bonus.c ft_printf_bonus_conversions1.c ft_printf_bonus_conversions2.c ft_printf_bonus_flags1.c ft_printf_bonus_flags2.c ft_printf_bonus_utils.c ft_printf_bonus_uitoa.c
	cp libft/libft.a $(NAME)
	ar rc $(NAME) ft_printf_bonus.o ft_printf_bonus_conversions1.o ft_printf_bonus_conversions2.o ft_printf_bonus_flags1.o ft_printf_bonus_flags2.o ft_printf_bonus_utils.o ft_printf_bonus_uitoa.o

.PHONY: all clean fclean re bonus test-bonus