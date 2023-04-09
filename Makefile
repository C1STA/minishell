NAME = minishell
CC = gcc -Wall -Werror -Wextra -g
SRC = main.c \
	parsing/lexer/manipulate_input.c \
	parsing/lexer/init_src_token.c \
	parsing/lexer/manipulate_token.c \
	parsing/lexer/manipulate_token2.c \
	parsing/parser/parser.c \
	parsing/parser/ft_pipe.c \
	parsing/parser/guillemets.c \
	parsing/parser/in_out.c \
	parsing/parser/manip_env.c \
	parsing/parser/decoupe_ast_no_quotes.c \
	parsing/parser/final_ast.c \
	parsing/parser/manip_node_commannd.c \
	parsing/parser/manip_node_redir.c \
	parsing/parser/exception.c \
	parsing/parser/final_check_expand.c \
	signaux/signal.c \
	builtin/exit.c \
	builtin/export_with_option.c \
	builtin/ft_unset.c \
	ft_free/ft_free.c \
	error_pars.c \
	exe/redir.c \
	exe/redir_utils.c \
	exe/heredoc.c \
	exe/heredoc_remove.c \
	exe/heredoc_signal.c \
	exe/pipex.c \
	exe/pipex_init.c \
	exe/pipex_errors.c \
	exe/struct.c \
	exe/exec.c \
	exe/childs.c \
	exe/ft_strcmp.c \
	exe/ft_strjoin_free.c \
	exe/free_exe.c \
	exe/print_status.c

OBJ = $(SRC:%.c=%.o) 


all: $(NAME)

$(NAME) : $(OBJ)
		$(MAKE) --no-print-directory -C libft
		$(CC) $(OBJ) libft/libft.a -o $(NAME) -lreadline -g3

%.o : %.c
		$(CC) -c $< -o $@

clean :
	rm -f $(OBJ)
	make fclean -C libft
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re