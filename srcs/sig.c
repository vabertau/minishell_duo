/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzaz <hzaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:23:58 by hzaz              #+#    #+#             */
/*   Updated: 2024/05/07 15:25:39 by hzaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
