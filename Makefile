NAME = minishell

LIST =	main.c				parser/parse_err.c			builtin/export_builtin.c\
		sort_env.c			parser/replace_var.c		builtin/unset_builtin.c\
		child.c				parser/redirects.c			builtin/exit_builtin.c\
		utils.c				parser/parse_env.c			builtin/echo_builtin.c\
		sh_lvl.c			parser/parser.c				builtin/pwd_builtin.c\
		signals.c			parser/parse_err_sec.c		builtin/env_builtin.c\
		redirects.c			parser/redirects_common.c	builtin/cd_builtin.c\
		pipe.c				parser/parse_err_red.c\
		check_open.c		parser/quotes.c\
		pipex.c				parser/true_free.c\
		heredoc.c\
		free_all.c\

OBJ = $(LIST:.c=.o)

LIBFT_DIR =	./libft

LIBFT =	./libft/libft.a

RDLN = -lreadline -I~/.brew/Cellar/readline/8.1.1/include

CC = gcc

CFLAGS = -Wall -Werror -Wextra

%.o:  %.c Makefile minishell.h
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all : $(NAME)


$(NAME):	$(OBJ) $(LIBFT) Makefile minishell.h
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RDLN) -o $(NAME) -lreadline -L \
	~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include

FORCE :
$(LIBFT): FORCE
	make -C $(LIBFT_DIR)

re : fclean all


clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ)

fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)


.PHONY : all clean fclean re bonus
