NAME = minishell

CC = cc $(FLAGS) -g

#FLAGS = -Wall -Werror -Wextra

FILENAMES = main.c get_input.c lexer.c nb_tokens.c spaces_bet_tokens.c \
exit_free.c skip_q.c malloc_tokens.c init_data.c fill_tokens.c ft_quotesplit.c \
copy_bet_q.c fill_types.c check_unclosedq.c parsing_error.c checks.c check_schar_error.c \
check_pipe_ext.c pnb_cmd.c parser.c pmalloc_exec.c pfill_full_cmd.c pfill_split_cmd.c pfill_redir.c \
pinit_exec.c executor.c

SRCS = $(addprefix srcs/, $(FILENAMES))

OBJS = $(SRCS:.c=.o)

FT_PRINTF = libftprintf/libftprintf.a

FT_PRINTF_PATH = libftprintf

$(NAME): $(FT_PRINTF) $(OBJS)
	$(CC) $(OBJS) $(FT_PRINTF) -lreadline -o $(NAME)

$(FT_PRINTF):
	make -C $(FT_PRINTF_PATH) all

clean:
	make -C $(FT_PRINTF_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(FT_PRINTF_PATH) fclean
	rm -f $(NAME)

re: fclean all

all: $(NAME)
