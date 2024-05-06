/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:43:54 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/06 18:36:28 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_input_redirection(t_token *redir) {
    int fd = open(redir->word, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
}

void handle_output_redirection(t_token *redir, int fd) {

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (redir->next == NULL || redir->next->type != RIGHT1 || redir->next->type != RIGHT2) {
        dup2(fd, STDOUT_FILENO);
    }
    close(fd);
}



void handle_append_redirection(t_token *redir, int fd) {
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (redir->next == NULL || redir->next->type != RIGHT1 || redir->next->type != RIGHT2) {
        dup2(fd, STDOUT_FILENO);
    }
    close(fd);
}




void handle_redirections(t_exec *cmd) {
    int fd;
    for (t_token *redir = cmd->redir; redir != NULL; redir = redir->next) {
        if (redir->type == LEFT1) {
            handle_input_redirection(redir);
        }
        else if (redir->type == RIGHT1) {
            fd = open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            handle_output_redirection(redir, fd);

        }
        else if (redir->type == LEFT2) {
            //handle_here_document(redir);
            handle_input_redirection(redir);
        }
        else if (redir->type == RIGHT2) {
            fd = open(redir->word, O_WRONLY | O_CREAT | O_APPEND, 0644);
            handle_append_redirection(redir, fd);
        }
        else {
            // Pas d'action nécessaire pour les autres types
        }
    }
}

void prepare_out1(t_data *shell) {
    if (shell == NULL || shell->exec == NULL) return;  // Ajouter cette vérification

    int fd;
    t_exec *current_cmd = shell->exec;
    while (current_cmd) {
        t_token *redir = current_cmd->redir;
        while (redir) {
            if (redir->type == RIGHT1) {
                fd = open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("open failed");
                    continue;  // Continue même en cas d'erreur d'ouverture
                }
                close(fd);
            }
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }
}

void prepare_out2(t_data *shell) {
    if (shell == NULL || shell->exec == NULL) return;  // Ajouter cette vérification

    int fd;
    t_exec *current_cmd = shell->exec;
    while (current_cmd) {
        t_token *redir = current_cmd->redir;
        while (redir) {
            if (redir->type == RIGHT2) {
                fd = open(redir->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd == -1) {
                    perror("open failed");
                    continue;  // Continue même en cas d'erreur d'ouverture
                }
                close(fd);
            }
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
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
                full_path = ft_strjoin_free2("/tmp/heredoc_", counter_str); // 1 indique de libérer counter_str

                fd = open(full_path, O_RDWR | O_CREAT | O_TRUNC, 0600);
                if (fd == -1) {
                    perror("open");
                    exit(EXIT_FAILURE);
                }
                while ((line = readline("heredoc> ")) != NULL) {
                    if (strcmp(line, redir->word) == 0) {
                        free(line);
                        break;
                    }
                    write(fd, line, strlen(line));
                    write(fd, "\n", 1);
                    free(line);
                }
                close(fd);
                // Mise à jour du mot à rediriger avec le nouveau nom de fichier
                free(redir->word); // Libérer l'ancien mot si nécessaire
                redir->word = strdup(full_path); // Stocker le nom du fichier temporaire
                free(full_path); // Nettoyer la mémoire
            }
            redir = redir->next;
        }
        current_cmd = current_cmd->next;
    }
}

// Modification dans executor

     // Appel avant de commencer les forks

// Modifie handle_input_redirection pour gérer les fichiers temporaires



// Exécute une commande individuelle.
int exec_cmd(t_data *shell, t_exec *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*ret;
	char	**f;

	handle_redirections(cmd);
	j = 0;
	i = -1;
	f =  cmd->split_cmd;//ft_split(cmd->str, ' ');
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
						execve(ret, f, shell->env);

			}

		}
		
	}
	ft_printf("command not found: %s\n", ++f[0]); // utiliser putstr_fd
		if (!cmd->next)
			shell->last_return_code = 127;
	return 0;
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
    int i = 0, status = 0;
    pid_t pid, last_pid;

    prepare_heredocs(shell);
    prepare_out1(shell);
    prepare_out2(shell);
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
        } else if (pid == 0) { // Processus enfant
            if (i < shell->nb_cmd - 1) {
                dup2(pipe_fds[i * 2 + 1], STDOUT_FILENO);
            }
            if (i > 0) {
                dup2(pipe_fds[(i - 1) * 2], STDIN_FILENO);
            }

            for (int j = 0; j < 2 * (shell->nb_cmd - 1); j++) {
                close(pipe_fds[j]);
            }
			if (i == shell->nb_cmd - 1)
				shell->last_pid = pid;
            exec_cmd(shell, current_cmd);
            exit(EXIT_FAILURE); // Si exec_cmd retourne, c'est une erreur
        } else {
            if (i == shell->nb_cmd - 1) { // Dernier processus créé
                shell->last_pid = pid;
            }
        }

        current_cmd = current_cmd->next;
        i++;
    }

    for (i = 0; i < 2 * (shell->nb_cmd - 1); i++) {
        close(pipe_fds[i]);
    }

    // Attente spécifique du dernier processus
    // if (shell->last_pid) {
    //     waitpid(shell->last_pid, &status, 0);  // Attendre spécifiquement le dernier processus
    //     if (WIFEXITED(status)) {
    //         shell->last_return_code = WEXITSTATUS(status);
    //     }
    // }
	// else if (shell->last_pid == -1)
	// 	 shell->last_return_code = 127;
    // Attente des autres processus enfants
    while ((pid = wait(NULL)) > 0);

    return shell->last_return_code; // Retourner le code de sortie du dernier processus
}

