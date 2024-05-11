/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:47:00 by hedi              #+#    #+#             */
/*   Updated: 2024/05/11 15:02:43 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup_var(const char *s, int n)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (i <= n)
		ret = malloc(sizeof(char) * (i + 1));
	else
		ret = malloc(sizeof(char) * (n + 1));
	if (!ret)
		return (0);
	while (j < i && j < n)
	{
		ret[j] = s[j];
		j++;
	}
	if (ret[j - 1] == '=')
		--j;
	ret[j] = '\0';
	return (ret);
}

char	**malloc_var(int i, char *s, int j, int n)
{
	char **ret;

	ret = malloc(sizeof(char *) * (n + 1));
	if (!ret)
		return (NULL);
	ret[0] = ft_strndup_var(s, (j));
	if (!ret[0])
	{
		free(ret);
		return (NULL);
	}
	if(n == 2)
	{
		ret[1] = ft_strdup(s + i);
		if (!ret[1])
		{
			free(ret[0]);
			free(ret);
			return (NULL);
		}
		ret[2] = NULL;
	}
	else
		ret[1] = NULL;
	return (ret);
}
char **split_var(char *s, t_data *shell)
{
	int	i;
	int	n;
	int	j;
	char **ret;

	i = 0;
	while (s && s[i] && s[i] != '=' && s[i] != '+')
		i++;
	n = 1;
	j = i;
	if (s[i])
		n = 2;
	if (s[i] == '+' && s[i] == '=')
		i += 2;
	else if (s[i] == '=')
		i++;
	ret = malloc_var(i, s, j, n);
	return (ret);
}
int	find_index_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=' )
		i++;
	return (i);
}
int	var_in_env(char *s, t_data *shell)
{
	int		ret;
	int		j;
	char 	*tmp;
	char	**var;

	var = split_var(s, shell);
	if (!var)
	{
		perror("malloc");
		exit_free(shell, EXIT_FAILURE);
	}
	ret = -1;
	j = -1;
	while (shell->env[++j])
	{
		tmp = ft_strndup(shell->env[j], find_index_env(shell->env[j]));
		if (ft_same_str_exact_free1(tmp, var[0]))
			ret = j;
	}
	if (var[1])
		free(var[1]);
	free(var[0]);
	free(var);
	return (ret);
}
int check_plus(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '=' && s[i] != '+')
		i++;
	if (s[i] == '+')
		return(1);
	else if (s[i] == '=')
		return (0);
	else 
		printf("error_checkplus");
	return (-1);
}

void	ft_update_env(char *str, t_data *shell, int pos)
{
	char **s;
	int	index;

	s = split_var(str, shell);
	//printf("\n%s\n", str);
	if (!s)
		return ;
	if (check_plus(str))
		shell->env[pos] = join_free1(shell->env[pos], s[1]);
	else{
		index = find_index_env(shell->env[pos]);
		if (shell->env[pos][index + 1] == '=' && !s[1])
		{
			free(shell->env[pos]);
			shell->env[pos] = ft_strjoin(s[0], "=""");
		}
		free(shell->env[pos]);
		shell->env[pos] = join_free1(ft_strjoin(s[0], "="),s[1]);
	}
	
	
}

void ft_add_env(char *s, t_data *shell)
{
    int i = 0;
    char **new_env;
    char *tmp;

    // Trouver la taille actuelle de shell->env
    while (shell->env && shell->env[i])
        i++;

    // Créer une nouvelle entrée pour la nouvelle variable
    tmp = join_free2(join_free1(ft_strndup_var(s, ft_strlen(s)), "="), ft_strdup(ft_strchr(s, '=') + 1));
    if (!tmp)
        return;

    // Allouer de la mémoire pour le nouveau tableau d'environnement
    new_env = malloc(sizeof(char *) * (i + 2));  // +2 pour la nouvelle variable et NULL terminateur
    if (!new_env)
    {
        free(tmp);
        return;
    }

    // Copier les anciennes valeurs
    for (int j = 0; j < i; j++)
        new_env[j] = shell->env[j];

    // Ajouter la nouvelle variable
    new_env[i] = tmp;
    new_env[i + 1] = NULL;

    // Libérer l'ancien tableau si nécessaire
    free(shell->env);

    // Mettre à jour l'environnement
    shell->env = new_env;

    printf("Added %s to env\n", shell->env[i]);  // Debug pour voir ce qui est ajouté
}


int	ft_putenv(char *s, t_data *shell)
{
	int pos;

	pos = var_in_env(s, shell);
	//printf("\n%s\n", s);
	if (pos > -1)
		ft_update_env(s, shell, pos);
	else
		ft_add_env(s, shell);
	return 1;
}

void ft_printf_var_env(char *var)
{
	write(STDOUT_FILENO,"declare -x ", 11);
	write(STDOUT_FILENO, var, ft_strlen(var));
	write(STDOUT_FILENO, "\n", 1);
}

int check_cmd(char *s)
{
	int i;

	i = 0;
	if (!s[0] || (s[0] != '_' && !ft_isalpha(s[0])))
		return (0);
	while(++i && s && s[i] && s[i] != '=' && s[i] != '+')
		if ((s[i] != '_' && !ft_isalnum(s[i])))
			return (0);
	if (s[i] == '+' && s[i + 1] != '=')
		return (0);
	return (1);
}

int	ft_export(char **split_cmd, t_data *shell)
{
	int	i;
	char *tmp;
	//printf("\n%s\n", split_cmd[1]);
	if (split_cmd[1] == NULL)
	{
		i = -1;
		while (shell->env && shell->env[++i])
			ft_printf_var_env(shell->env[i]);
	}
	i = 0;
	while (split_cmd[++i] != NULL)
	{
		if (!check_cmd(split_cmd[i]))
		{
			tmp = ft_strjoin("bash: export: `", split_cmd[i]);
			ft_putstr_fd_free(join_free1(tmp, "': not a valid identifier\n"), 2);
		}
		else if (ft_putenv(split_cmd[i], shell) != 1) // Add to the environment
		{
			perror("export");
			exit_free(shell, EXIT_FAILURE);
		}
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