/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:32:33 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/08 19:40:55 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_tokens(t_data *data)
{
	int		i;
	t_token	*tmp;

	i = 0;
	data->token = malloc(sizeof(t_token)); // CHECKED
	if (!data->token)
		exit_free(data, -1);
	tmp = data->token;
	while (i < data->nb_tokens - 1)
	{
		tmp->i = i; // rm in the end if not useful
		tmp->word = NULL;
		tmp->next = malloc(sizeof(t_token)); // CHECKED
		if (!tmp->next)
			exit_free(data, -1);
		tmp = tmp->next;
		i++;
	}
	tmp->i = i;
	tmp->word = NULL;
	tmp->next = NULL;
}
