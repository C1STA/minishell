NAME = ft_printf

CC = gcc -Wall -Wextra -Werror

SRC = ft_putchar_fd.c \
    ft_putstr_fd.c \
    ft_putnbr_fd.c \
    ft_printf.c \
    count_hex_spe.c \
    count_int_spe.c \
    ft_putnbr_hex_maj.c \
    ft_putnbr_hex_mini.c \
    ft_putnbr_spe_fd.c \
    ft_putnbr_unsigned_fd.c \
    ft_putstr_spe_fd.c \
    printpointer.c \
    printstr.c \
    countpointer.c \
    ft_put_pointer.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	ar rc $(NAME) $^

%.o : %.c
	$(CC) -c $^

bonus : $(OBJ) $(BONUS_OBJ)
	ar rc $(NAME) $^

clean :
	rm -f $(OBJ) $(BONUS_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
