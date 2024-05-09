/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fixed_cmdline_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:09:28 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/09 17:09:39 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Calculates new len of cmdline after adding spaces
*/

int	fixed_cmdline_len(char *cmdline)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmdline[i])
	{
		i += skip_sq(&(cmdline[i]));
		if (cmdline[i] == '<' || cmdline[i] == '>' || cmdline[i] == '|')
		{
			if (i > 0 && cmdline[i - 1] != '<' && cmdline[i - 1] != '>'
				&& cmdline[i - 1] != '|' && cmdline[i - 1] != ' ')
				ret++;
			if (cmdline[i + 1] != '<' && cmdline[i + 1] != '>'
				&& cmdline[i + 1] != '|' && cmdline[i + 1] != ' ')
				ret++;
		}
		i++;
	}
	return (ret + ft_strlen(cmdline));
}
