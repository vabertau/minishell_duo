void handle_sigint_interactive(int sig) {
    signal_count++;  // Incrémente le compteur de signaux global
    write(STDOUT_FILENO, "\nmini-shell> ", 13);  // Affiche un nouveau prompt sur une nouvelle ligne
}
void handle_sigint_heredoc(int sig) {
    signal_count++;  // Incrémente le compteur de signaux
    // Ici, tu pourrais ajouter du code pour nettoyer ou ignorer le heredoc en cours
    write(STDOUT_FILENO, "\nmini-shell> ", 13);  // Retourne au prompt principal
}
void handle_sigint_command(int sig) {
    signal_count++;  // Incrémente le compteur de signaux
    // Ajoute ici du code pour terminer proprement la commande bloquante en cours
    write(STDOUT_FILENO, "\nmini-shell> ", 13);  // Affiche un nouveau prompt
}
void handle_sigquit(int sig) {
    // Pour CTRL-\ dans les modes interactif et heredoc, ne fait rien
}
void handle_sigquit_command(int sig) {
    signal_count++;  // Incrémente le compteur de signaux
    abort();  // Génère un signal SIGABRT pour créer un dump core
}
