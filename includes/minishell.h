#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
# include "../libftprintf/ft_printf.h"

typedef enum s_type{
	WORD,
	PIPE,
	RIGHT1,
	RIGHT2,
	LEFT1,
	LEFT2,
	DQUOTE,
}	t_type;

typedef struct s_token{
	int					i;
	char				*word;
	t_type				type;
	struct s_token		*next;
}				t_token;

typedef struct s_exec{
	char			*full_cmd;
	char			**split_cmd;
	int				nb_redir;
	t_token			*redir;
	struct s_exec	*next;
}				t_exec;

typedef struct s_data{
	char	*cmdline;
	int		nb_tokens;
	int		nb_sq;
	int		nb_dq;
	int		nb_cmd;
	t_token	*token;
	t_type type;
	t_exec	*exec;
	bool	*is_bq;
}				t_data;

// ====== READLINE ======

void	get_input(t_data *data);

// ====== INIT_DATA ======

void	init_data(t_data *data);

// ===== CHECKER =====

int		check_unclosedq(t_data *data);
void	parsing_error(t_data *data);
void	checks(t_data *data);
void	check_schar_error(t_data *data);
void	check_pipe_ext(t_data *data);

// ====== LEXER ======

void	lexer(t_data *data);
void	nb_tokens(t_data *data);
int		spaces_bet_tokens(t_data *data);
int		skip_sq(char *cmdline);
int		skip_dq(char *cmdline);
void	malloc_tokens(t_data *data);
void	fill_tokens(t_data *data);
char	**ft_quotesplit(t_data *data, char const *s);
void    copy_bet_sq(int *i, int *j, const char *s, char *tmp);
void    copy_bet_dq(int *i, int *j, const char *s, char *tmp);
void    fill_types(t_data *data);

// ===== PARSER =====

void	nb_cmd(t_data *data);
void	parser(t_data *data);
void	malloc_exec(t_data *data);
void	fill_full_cmd(t_data *data);
void	fill_split_cmd(t_data *data);
void	nb_redir(t_data *data);
void	fill_redir(t_data *data);
void	init_exec(t_data *data);

// ====== EXIT ======

void	exit_free(t_data *data, int exit_code);
void	free_bf_newprompt(t_data *data);
