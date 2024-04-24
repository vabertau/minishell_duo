/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:43:14 by vabertau          #+#    #+#             */
/*   Updated: 2024/04/18 15:09:35 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	fill_tokens(t_data *data)
{
	t_token	*token;
	char	**tmp;
	int		i;

	i = 0;
	token = data->token;
	tmp = ft_quotesplit(data, data->cmdline);
	if (tmp == NULL)
			exit_free(data, -1);
	i = 0;
	while (i < data->nb_tokens)
	{
		token->word = tmp[i];
		token = token->next;
		i++;
	}
	i = 0;
	free (tmp);
}
