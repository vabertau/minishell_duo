/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:02:38 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/07 18:52:28 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
static int	free_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
*/
static void	free_token(t_token *token)
{
	t_token		*tmp;
	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		if (tmp->word != NULL)
			free(tmp->word);
		// if (tmp->fd != -1)
		// 	if (close(tmp->fd) == -1)
		// 		perror("close");
		free(tmp);
	}
}

void	free_bf_newprompt(t_data *data)
{
	if (data->cmdline != NULL)
		free(data->cmdline);
	free_token(data->token);
}

void	free_exec(t_data *data)
{
	t_exec	*tmp_exec;
	t_exec	*tmp_exec_tf;

	tmp_exec = data->exec;
	while (tmp_exec)
	{
		if (tmp_exec->redir)
			free (tmp_exec->redir); //free redir FREE TO DO IN REDIR
		if (tmp_exec->full_cmd)
			free(tmp_exec->full_cmd); // free full_cmd
		if (tmp_exec->split_cmd)
			free(tmp_exec->split_cmd); // free split cmd only ** to free cause * are pointers to words
		tmp_exec_tf = tmp_exec;
		tmp_exec = tmp_exec->next;
		free(tmp_exec_tf); //free exec
	}
}

// SHOULD NOT EXIT AS MINISHELL IS A LOOP GIVING BACK PROMPT

void	free_all(t_data *data)
{
	if (data->cmdline != NULL)
		free(data->cmdline);
	if (data->token)
		free_token(data->token);
	if (data->exec)
		free_exec(data);
	if (data->is_bq)
		free(data->is_bq);
}

void	exit_free(t_data *data, int exit_code)
{
	free_all(data);
	exit(exit_code);
}

void	set_exitloop_free(t_data *data)
{
	//free_all(data);
	data->sh_exit_loop = 1;
}
