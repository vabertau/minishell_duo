/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:59:10 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/06 16:30:11 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Take the tokens and organize them in a structure containing all the elements necessary to execve
*/
void	parser(t_data *data)
{
	nb_cmd(data);
	malloc_exec(data);
	init_exec(data);
	fill_full_cmd(data);
	fill_split_cmd(data);
	fill_redir(data);
}
