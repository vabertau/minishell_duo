# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <dirent.h>
# include <string.h>
# include <stdio.h>
# include <curses.h>
# include <sys/ioctl.h>
# include <stddef.h>
# include <termios.h>
# include <sys/stat.h>
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
	char	**env;
	int	*is_bq;
	int		last_pid;
	int		last_return_code;
	bool	sh_exit_loop;
	bool	void_expand;
}				t_data;

// ====== READLINE ======

void	get_input(t_data *data);

// ====== INIT_DATA ======

void	init_data(t_data *data, char **env);

// ===== CHECKER =====

int		check_unclosedq(t_data *data);
void	parsing_error(t_data *data);
void	checks(t_data *data);
void	check_schar_error(t_data *data);
void	check_pipe_ext(t_data *data);
void	check_empty(t_data *data);

// ===== CHECKER AFTER REDIR =====

void	check_redirfile(t_data *data);

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

// ===== EXPANDS =====

int expands(t_data *data);

// ====== EXIT ======

void	exit_free(t_data *data, int exit_code);
void	free_bf_newprompt(t_data *data);
void	set_exitloop_free(t_data *data);

// ====== EXEC ======

char	*ft_strjoin_free1(char const *s1, char const *s2);

// Prototypes des fonctions de gestion de redirection
void	handle_input_redirection(t_token *redir);
void	handle_output_redirection(t_token *redir, int fd);
void	handle_here_document(t_token *redir);
void	handle_append_redirection(t_token *redir, int fd);
void	handle_redirections(t_exec *cmd);

// Prototypes des fonctions d'exécution de commandes
int	exec_cmd(t_data *shell, t_exec *cmd);
int	executor(t_data *shell);

// Prototype de la fonction de manipulation de chaînes et utilitaires
char	*ft_strjoin_free1(char const *s1, char const *s2);
char	*ft_strjoin_free2(char const *s1, char const *s2);
int	ft_same_str(char *str1, char *str2, size_t n);

// Prototype de la fonction de gestion des pipes
int	init_pipes(t_data *shell, int *pipe_fds);

void prepare_out2(t_data *shell);
void prepare_out1(t_data *shell);
