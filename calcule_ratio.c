// Fonction pour calculer le ratio de réservation
double calculerRatio(int nb_sieges_reserves, int nb_sieges_total) {
    if (nb_sieges_total == 0) {
        return 0.0; // Pour éviter la division par zéro
    }
    return ((double)nb_sieges_reserves / nb_sieges_total) * 100;
}
