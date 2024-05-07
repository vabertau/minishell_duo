/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:43:54 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/07 16:40:43 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int safe_open(const char *pathname, int flags, mode_t mode, t_data *shell) {
    int fd;
    
    fd = open(pathname, flags, mode);
    if (fd == -1) {
        perror("open");
        exit_free(shell, EXIT_FAILURE);
    }
    return fd;
}

void safe_close(int fd, t_data *shell) {
    if (close(fd) == -1) {
        perror("close");
        exit_free(shell, EXIT_FAILURE);
    }
}

void safe_dup2(int oldfd, int newfd, t_data *shell) {
    if (dup2(oldfd, newfd) == -1) {
        perror("dup2");
        exit_free(shell, EXIT_FAILURE);
    }
}


void handle_input_redirection(t_token *redir, t_data *shell) {
    int fd;
    fd = safe_open(redir->word, O_RDONLY, 0, shell);
    if (fd == -1) {
        perror("open");
        exit_free(shell,EXIT_FAILURE);
    }
    safe_dup2(fd, STDIN_FILENO, shell);
    safe_close(fd, shell);
}

void handle_output_redirection(t_token *redir, int fd, t_data *shell) {

    if (fd == -1) {
        perror("open");
        exit_free(shell,EXIT_FAILURE);
    }
    if (redir->next == NULL || redir->next->type != RIGHT1 || redir->next->type != RIGHT2) {
        safe_dup2(fd, STDOUT_FILENO, shell);
    }
    safe_close(fd, shell);
}



void handle_append_redirection(t_token *redir, int fd, t_data *shell) {
    if (fd == -1) {
        perror("open");
        exit_free(shell, EXIT_FAILURE);
    }
    if (redir->next == NULL || redir->next->type != RIGHT1 || redir->next->type != RIGHT2) {
        safe_dup2(fd, STDOUT_FILENO, shell);
    }
    safe_close(fd, shell);
}




void handle_redirections(t_exec *cmd, t_data *shell) {
    int fd;
    t_token *redir;

    redir = cmd->redir;
    while (redir != NULL) {
        if (redir->type == LEFT1 || redir->type == LEFT2) {
            handle_input_redirection(redir, shell);
        }
        else if (redir->type == RIGHT1 || redir->type == RIGHT2) {
            if (redir->type == RIGHT2)
                fd = safe_open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644, shell);
            else
                fd = safe_open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644, shell);
            handle_output_redirection(redir, fd, shell);

        }
         redir = redir->next;
    }
}



// Nouvelle fonction pour préparer les heredocs
void prepare_heredocs(t_data *shell) {
    int counter = 0;
    int fd;
    char *line;
    char *counter_str, *full_path;

    t_exec *current_cmd = shell->exec;
    while (current_cmd) {
        t_token *redir = current_cmd->redir;
        while (redir) {
            if (redir->type == LEFT2) { // Type LEFT2 pour heredoc
                counter_str = ft_itoa(counter++);
                full_path = ft_strjoin_free2("/tmp/heredoc_", counter_str); 
                fd = safe_open(full_path, O_RDWR | O_CREAT | O_TRUNC, 0600, shell);
                while ((line = readline("heredoc> ")) != NULL) {
                    if (ft_strcmp(line, redir->word) == 0) {
                        free(line);
                        break;
                    }
                    write(fd, line, strlen(line));
                    write(fd, "\n", 1);
                    free(line);
                }
                safe_close(fd, shell);
                free(redir->word); // Libérer l'ancien mot si nécessaire
                redir->word = ft_strdup(full_path); // Stocker le nom du fichier temporaire
                free(full_path); // Nettoyer la mémoire
            }
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }
}


int exec_cmd(t_data *shell, t_exec *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*ret, *ret2,*ret3;
	char	**f;

	handle_redirections(cmd, shell);
	j = 0;
	i = -1;
	f =  cmd->split_cmd;
	f[0] = ft_strjoin("/",f[0]);
	if (access(f[0], F_OK) == 0)
		execve(f[0], f, shell->env);
	while (shell->env[++i] != NULL && shell->env)
	{
		ret = ft_substr(shell->env[i], 0, 5);
		if (ft_same_str(ret, "PATH=", 5) == 1)
		{
			j = 5;
			while (shell->env[i][j] && shell->env[i][++j] != '\0' && shell->env)
			{
				k = j;
				while (shell->env[i][j] != ':' && shell->env[i][j] && shell->env)
					j++;
				ret = ft_strjoin_free1(ft_substr(shell->env[i], k, ((j) - k)), f[0]);
				if (shell->env[i][j] == ':')
					if (access(ret, F_OK) == 0)
					{
						setup_signal_handlers(handle_sigint_command, handle_sigquit_command);
						execve(ret, f, shell->env);
					}

			}
		}	
	}
	ret2 = ft_strjoin("command not found: ", f[0]);
	ret3 = ft_strjoin_free1(ret2, "\n");
	ft_putstr_fd(ret3, 2);
    free(ret3);
	exit_free(shell,127);
	return 127;
}

char	*ft_strjoin_free1(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i] && dest)
		dest[k++] = s1[i++];
	while (s2 && s2[j] && dest)
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((void *)s1);
	return (dest);
}

char	*ft_strjoin_free2(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	len = (ft_strlen(s1) + ft_strlen(s2));
	dest = malloc(len + 1 * sizeof(char));
	if (!dest)
		return (NULL);
	while (s1 && s1[i] && dest)
		dest[k++] = s1[i++];
	while (s2 && s2[j] && dest)
		dest[k++] = s2[j++];
	dest[k] = '\0';
	free((void *)s2);
	return (dest);
}

int	ft_same_str(char *str1, char *str2, size_t n)
{
	int	i;

	i = -1;
	while ((++i < (int)n) && str1 && str2)
	{
		if (str1[i] != str2[i])
		{
			free(str1);
			return (0);
		}
	}
	free(str1);
	return (1);
}

int	init_pipes(t_data *shell, int *pipe_fds)
{
	int		i;

	i = 0;
	while (i < (shell->nb_cmd - 1))
	{
		if (pipe(pipe_fds + i * 2) < 0)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (1);
}

int executor(t_data *shell) {
    int pipe_fds[2 * (shell->nb_cmd - 1)];
    int i = 0;
    int status;
    pid_t pid;
    int j;

    prepare_heredocs(shell);
    if (shell->nb_cmd > 1) {
        if (!init_pipes(shell, pipe_fds))
            return (0);
    }
    t_exec *current_cmd = shell->exec;
    while (current_cmd != NULL) {
        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { 
            if (i < shell->nb_cmd - 1) {
                safe_dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO, shell);
            }
            if (i > 0) {
                safe_dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO, shell);
            }
            j = 0;
            while (j < 2 * (shell->nb_cmd - 1)) {
                close(pipe_fds[j]);
                j++;
            }
            exec_cmd(shell, current_cmd);
            exit_free(shell, EXIT_FAILURE);
            
        }
        else
            current_cmd->pid = pid;
        current_cmd = current_cmd->next;
        i++;
    }
    i = 0;
    while (i < 2 * (shell->nb_cmd - 1)) 
        close(pipe_fds[i++]);
    waitpid(pid, &status, 0);
    shell->last_return_code = WEXITSTATUS(status);
    waitpid(-1, &status, 0);
    return shell->last_return_code;
}

