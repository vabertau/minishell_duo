/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_ext.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:42:47 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/08 19:42:11 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks if the cmdline begins or ends with a pipe and returns parsing error if it is the case
*/
void	check_pipe_ext(t_data *data)
{
	int		i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i] && cmdline[i] == ' ')
		i++;
	if (cmdline[i] == '|')
		return ((void)parsing_error(data));
	while (cmdline[i])
		i++;
	if (i > 0)
		i--;
	while (i > 0 && cmdline[i] == ' ')
		i--;
	if (i > 0 && cmdline[i] == '|')
		return ((void)parsing_error(data));
}
