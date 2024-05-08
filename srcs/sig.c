/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hedi <hedi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:58 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/08 22:36:50 by hedi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal_count = 0;

void	handle_sigint_interactive(int sig)
{
	g_signal_count++;
	write(2, "\nminishell\% ", 13);
	return ((void)sig);
}

// Gestionnaire pour SIGINT dans un heredoc
void	handle_sigint_heredoc(int sig)
{
	g_signal_count++;
	write(2, "minishell\%", 13);
	return ((void)sig);
}

// Gestionnaire pour SIGINT dans une commande bloquante
void	handle_sigint_command(int sig)
{
	g_signal_count++;
	write(2, "^C\nminishell\% ", 15);
	return ((void)sig);
}

// Gestionnaire pour SIGQUIT dans une commande bloquante
void	handle_sigquit_command(int sig)
{
	g_signal_count++;
	write(2, "Quit (core dumped)\n", 19);
	return ((void)sig);
}

// Gestionnaire pour SIGQUIT qui ne fait rien (utilisé pour mode interactif et heredoc)
void	handle_sigquit(int sig)
{
	return ((void)sig);
}

void	setup_signal_handlers(void (*sigint_handler)(int),
		void (*sigquit_handler)(int))
{
	struct sigaction	sa;

	// Configuration pour SIGINT
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	// Configuration pour SIGQUIT
	sa.sa_handler = sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

