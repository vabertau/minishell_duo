/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabertau <vabertau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:58 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/07 15:40:30 by vabertau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Gestionnaire pour SIGINT en mode interactif

void handle_sigint_interactive(int sig) {
    signal_count++;
    write(STDOUT_FILENO, "\nmini-shell> ", 13);
}

// Gestionnaire pour SIGINT dans un heredoc
void handle_sigint_heredoc(int sig) {
    signal_count++;
    write(STDOUT_FILENO, "\nmini-shell> ", 13);
}

// Gestionnaire pour SIGINT dans une commande bloquante
void handle_sigint_command(int sig) {
    signal_count++;
    write(STDOUT_FILENO, "^C\nmini-shell> ", 15);
}

// Gestionnaire pour SIGQUIT dans une commande bloquante
void handle_sigquit_command(int sig) {
    signal_count++;
    abort();
}

// Gestionnaire pour SIGQUIT qui ne fait rien (utilisé pour mode interactif et heredoc)
void handle_sigquit(int sig) {
    // Ne fait rien
}


void setup_signal_handlers(void (*sigint_handler)(int), void (*sigquit_handler)(int)) {

	struct sigaction sa;
    // Configuration pour SIGINT
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    // Configuration pour SIGQUIT
    sa.sa_handler = sigquit_handler;
    sigaction(SIGQUIT, &sa, NULL);
}

