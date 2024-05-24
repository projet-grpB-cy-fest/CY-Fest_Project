// Fonction pour scanner un entier
int better_scan_int(char *message) {
    int value;
    char buffer[64];
    while (1) {
        printf("%s", message);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // Gestion d'une erreur de saisie
            printf("Erreur de saisie. Veuillez saisir un entier.\n");
            continue;
        }
        if (sscanf(buffer, "%d", &value) != 1) {
            // Gestion d'une saisie incorrecte (non-entier)
            printf("Erreur de saisie. Veuillez saisir un entier.\n");
            continue;
        }
        break;
    }
    return value;
}