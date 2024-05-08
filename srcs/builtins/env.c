/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:47:00 by hedi              #+#    #+#             */
/*   Updated: 2024/05/09 01:04:03 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(char **split_cmd, char **env)
{
	int i = -1;
	int j = 0;
	if (split_cmd[1] == NULL)
	{
		while (env && env[++i])
		{
			write(STDOUT_FILENO,"declare -x ", 11);
			write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
		return (0);
	}
	i = 1;
	while (split_cmd[i] != NULL)
	{
		if (putenv(split_cmd[i]) != 0) // Add to the environment
		{
			perror("export");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **split_cmd)
{
	int i = 1;
	while (split_cmd[i] != NULL)
	{
		unsetenv(split_cmd[i]);
		i++;
	}
	return (0);
}

int	ft_env(char **envp)
{
	int i = 0;
	while (envp[i] != NULL)
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (0);
}