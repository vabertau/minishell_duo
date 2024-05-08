/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:50 by vabertau          #+#    #+#             */
/*   Updated: 2024/05/08 19:40:47 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->cmdline = NULL;
	data->token = NULL;
	data->token = NULL;
	data->exec = NULL;
	data->is_bq = NULL;
	data->env = envp;
}
