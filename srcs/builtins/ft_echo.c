/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:27:39 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/07 16:13:16 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **split_cmd)
{
	int		i;
	bool	nl_to_put;

	i = 1;
	nl_to_put = 1;
	if (split_cmd[1] && !ft_strncmp(split_cmd[1], "-n", 3))
	{
		nl_to_put = 0;
		i++;
	}
	while (split_cmd[i])
	{
		ft_putstr_fd(split_cmd[i], STDOUT_FILENO);
		if (split_cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl_to_put)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

/*
int	main(int argc, char **argv)
{
	if (argc < 2)
		return (-1);
	ft_echo(&(argv[1]));
	return (0);
}
*/
