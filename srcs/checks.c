/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:33:51 by vabertau          #+#    #+#             */
/*   Updated: 2024/04/25 12:16:24 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*returns 1 if cmdline is emtpy*/

static void	check_empty(t_data *data)
{
	int	i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == ' ')
			i++;
		else
			return ;
	}
	exit_free(data, 0); // NE DOIT PAS EXIT DOIT SORTIR DE LA BOUCLE WHILE
}

void	checks(t_data *data)
{
	check_empty(data);
	check_unclosedq(data);
	check_schar_error(data);
	check_pipe_ext(data);
}
