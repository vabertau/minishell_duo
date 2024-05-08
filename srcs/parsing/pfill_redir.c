/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfill_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:47:39 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/08 19:41:14 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Calculates the nb of redirections with the nb of > < >> << and fills data->exec->nb_redir
*/
void	nb_redir(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	int		i;
	int		nb_redir;

	i = 0;
	nb_redir = 0;
	tmp_exec = data->exec;
	tmp_token = data->token;
	while (i < data->nb_tokens)
	{
		if (tmp_token->type != WORD && tmp_token->type != PIPE)
			nb_redir++;
		if (tmp_token->type == PIPE || (i + 1) == data->nb_tokens)
		{
			tmp_exec->nb_redir = nb_redir;
			nb_redir = 0;
			tmp_exec = tmp_exec->next;
		}
		i++;
		tmp_token = tmp_token->next;
	}
}

/*
Malloc data->exec->nb_redirections nodes in t_exec. Those will be filled with
word = infile and type = >
*/
void	malloc_redir(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	t_token	*tmp_redir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp_exec = data->exec;
	tmp_token = data->token;
	while (i < data->nb_cmd)
	{
		j = 0;
		while (j < tmp_exec->nb_redir)
		{
			if (j == 0)
			{
				tmp_exec->redir = malloc(sizeof(t_token)); // CHECKED
				if (!tmp_exec->redir)
					exit_free(data, -1);
				tmp_redir = tmp_exec->redir;
			}
			else
			{
				tmp_redir->next = malloc(sizeof(t_token)); // CHECKED
				if (!tmp_redir)
					exit_free(data, -1);
				tmp_redir = tmp_redir->next;
			}
			j++;
		}
		if (j > 0)
		{
			tmp_redir->next = NULL;
		}
		tmp_exec = tmp_exec->next;
		i++;
	}
}
/*
Iterates on all the tokens
For each cmd, while j < tmp_exec->nb_redir,
*/
void	fill_redir(t_data *data)
{
	t_exec	*tmp_exec;
	t_token	*tmp_token;
	t_token	*previous_token;
	t_token	*tmp_redir;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb_redir(data);
	malloc_redir(data);
	tmp_exec = data->exec;
	tmp_token = data->token;
	tmp_redir = tmp_exec->redir;
	previous_token = NULL;
	while (i < data->nb_tokens)
	{
		if (tmp_token->type == WORD && (previous_token != NULL)
			&& (previous_token->type == RIGHT1 || previous_token->type == RIGHT2
				|| previous_token->type == LEFT1
				|| previous_token->type == LEFT2))
		{
			tmp_redir->word = tmp_token->word;
			tmp_redir->type = previous_token->type;
			tmp_redir = tmp_redir->next;
			j++;
		}
		if (j == tmp_exec->nb_redir)
		{
			if (tmp_exec->next == NULL)
				return ;
			tmp_exec = tmp_exec->next;
			tmp_redir = tmp_exec->redir;
			j = 0;
		}
		i++;
		previous_token = tmp_token;
		tmp_token = tmp_token->next;
	}
}
