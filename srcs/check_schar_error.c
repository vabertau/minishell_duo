/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_schar_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:06:04 by vabertau          #+#    #+#             */
/*   Updated: 2024/04/24 17:22:01 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
That function is called when a pipe is found. It checks that the next found character is not a pipe,
skipping spaces.
*/
static int	check_if_next_is_pipe(char *cmdline)
{
	int		i;

	i = 1;
	while (cmdline[i])
	{
		if (cmdline[i] != ' ' && cmdline[i] != '|')
			return (0);
		else if (cmdline[i] == ' ')
			i++;
		else if (cmdline[i] == '|')
			return (1);
	}
	return (0);
}

void	check_for_append_pipe(t_data *data)
{
	int	i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '>' || cmdline [i] == '<')
		{
			i++;
			while (cmdline[i] == '>' || cmdline[i] == '<' || cmdline[i] == ' ')
				i++;
			if (cmdline[i] == '|')
				parsing_error(data);
		}
		i++;
	}
}

/*
Checks for >|, >   |...
*/
void	check_for_append_space_append(t_data *data)
{
	int	i;
	char	*cmdline;
	bool	space_found;

	i = 0;
	space_found = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '<')
		{
			i++;
			while (cmdline[i] == ' ')
			{
				i++;
				space_found = 1;
			}
			if (cmdline[i] == '<' || cmdline[i] == '>')
			{
				if (space_found == 1)
					parsing_error(data);
			}
			space_found = 0;
		}
		if (cmdline[i] == '>')
		{
			i++;
			while (cmdline[i] == ' ')
			{
				i++;
				space_found = 1;
			}
			if (cmdline[i] == '<' || cmdline[i] == '>')
			{
				if (space_found == 1)
					parsing_error(data);
			}
			space_found = 0;
		}
		i++;
	}
}

void	check_schar_error(t_data *data)
{
	int	i;
	char	*cmdline;

	i = 0;
	cmdline = data->cmdline;
	while (cmdline[i])
	{
		if (cmdline[i] == '\'')
			i += skip_sq(&(cmdline[i]));
		if (cmdline[i] == '\"')
			i += skip_dq(&(cmdline[i]));
		if (cmdline[i] == '|')
			if (check_if_next_is_pipe(&(cmdline[i])) == 1)
				parsing_error(data);
		if ((cmdline[i] == '<' && cmdline[i + 1] == '<' && (cmdline[i + 2] == '<' || cmdline[i + 2] == '>'))
			|| (cmdline[i] == '>' && cmdline[i + 1] == '>' && (cmdline[i + 2] == '>' || cmdline[i + 2] == '<'))
			|| (cmdline[i] == '>' && cmdline[i + 1] == '<')
			|| (cmdline[i] == '<' && cmdline[i + 1] == '>'))
				parsing_error(data);
		check_for_append_space_append(data);
		check_for_append_pipe(data);
		i++;
	}
}
