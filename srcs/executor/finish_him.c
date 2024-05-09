/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_him.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:08:17 by hedi              #+#    #+#             */
/*   Updated: 2024/05/09 13:21:37 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_build(t_data *shell, char **f)
{
	if (ft_same_str(f[0], "echo", 4))
		shell->last_return_code = ft_echo(f);
	else if (ft_same_str(f[0], "cd", 2))
		shell->last_return_code = ft_cd(f, shell);
	else if (ft_same_str(f[0], "pwd", 3))
		shell->last_return_code = ft_pwd(shell);
	// else if (ft_same_str(f[0], "export", 6))
	// 	shell->last_return_code = ft_export(f, shell->env);
	// else if (ft_same_str(f[0], "unset", 5))
	// 	shell->last_return_code = ft_unset(f);
	// else if (ft_same_str(f[0], "env", 3))
		// shell->last_return_code = ft_env(shell->env);
	else if (ft_same_str(f[0], "exit", 4))
		ft_exit(f, shell); // Note que cette fonction peut arrêter le programme.
	else
		return ;
	exit_free(shell, 0);
}
// Aucun built-in correspondant trouvé
// if (ft_same_str(f[0], "echo", 4))
// 	ft_echo(f);
// else if (ft_same_str(f[0], "cd", 2))
// 	ft_cd();
// printf("test");

void	exec_path(t_data *sh, t_exec *cmd, char **f, char *tmp)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = -1;
	while (sh->env[++i] != NULL && sh->env)
	{
		ret = ft_substr(sh->env[i], 0, 5);
		if (ft_same_str_free(ret, "PATH=", 5))
		{
			j = 5;
			while (sh->env && sh->env[i][++j])
			{
				k = j;
				while (sh->env[i][j] != ':' && sh->env[i][j] && sh->env)
					j++;
				ret = join_free1(ft_substr(sh->env[i], k, ((j)-k)), tmp);
				if (sh->env[i][j] == ':')
					if (access(ret, F_OK) == 0)
						execve(ret, f, sh->env);
				free(ret);
			}
		}
	}
}

void	exec_cmd(t_data *shell, t_exec *cmd)
{
	char *ret;
	char *tmp;
	char **f;

	handle_redirections(cmd, shell);
	f = cmd->split_cmd;
	exec_build(shell, f);
	// printf("%s", f[0]);
	tmp = ft_strjoin("/", f[0]);
	if (access(tmp, F_OK) == 0)
		execve(tmp, f, shell->env);
	else
		exec_path(shell, cmd, f, tmp);
	ret = join_free1(ft_strjoin("command not found: ", f[0]), "\n");
	ft_putstr_fd_free(ret, 2);
	free(tmp);
	exit_free(shell, 127);
}