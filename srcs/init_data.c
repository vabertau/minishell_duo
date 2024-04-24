/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:48:50 by vabertau          #+#    #+#             */
/*   Updated: 2024/04/24 17:54:54 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data, char **envp)
{
	data->cmdline = NULL;
	data->token = NULL;
	data->token = NULL;
	data->exec = NULL;
	data->is_bq = NULL;
	data->env = envp;
}
