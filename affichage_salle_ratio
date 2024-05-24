// Fonction pour afficher la liste des salles créées pour la configuration
void afficherListeSalles(Salle salles[], int nb_salles) {
    printf("Liste des salles créées :\n");
    for (int i = 0; i < nb_salles; i++) {
        printf("%d. %s\n", i + 1, salles[i].nom_salle);
    }
}

// Fonction pour afficher le ratio de réservation pour chaque salle
void afficherRatioReservation(Salle salles[], int nb_salles) {
    printf("Ratio de réservation pour chaque salle :\n");
    for (int i = 0; i < nb_salles; i++) {
        double ratio = calculerRatio(salles[i].nb_siege_reserves, salles[i].nb_siege);
        printf("%s : %.2f%%\n", salles[i].nom_salle, ratio);
    }
}


//on pourra tester plus tard comme ca :

afficherListeSalles(salles, 4);
afficherRatioReservation(salles, 4);
