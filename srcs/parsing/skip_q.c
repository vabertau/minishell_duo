/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:05:27 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:41 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*if cmdline[i] is a quote, skips all until matching quote
*/
int	skip_sq(char *cmdline)
{
	int	i;

	i = 0;
	if (cmdline[i] != '\'')
		return (0);
	else
		i++;
	while (cmdline[i] && cmdline[i] != '\'')
		i++;
	return (i);
}

/*if cmdline[i] is a quote, skips all until matching quote
*/
int	skip_dq(char *cmdline)
{
	int	i;

	i = 0;
	if (cmdline[i] != '\"')
		return (0);
	else
		i++;
	while (cmdline[i] && cmdline[i] != '\"')
		i++;
	return (i);
}
