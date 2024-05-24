#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void afficher_creneaux_disponibles(char* creneaux[], int nb_creneaux) {
    printf("Creneaux horaires disponibles pour le 27 juin :\n");
    for (int i = 0; i < nb_creneaux; i++) {
        printf("%d. %s\n", i+1, creneaux[i]);
    }
}

int main() {
    // Initialisation des créneaux horaires disponibles
    char* creneaux[] = {"9:00-10:00", "10:00-11:00", "11:00-12:00", "13:00-14:00", "14:00-15:00", "15:00-16:00"};
    int nb_creneaux = sizeof(creneaux) / sizeof(creneaux[0]);

    // Mélanger les créneaux horaires disponibles
    srand(time(NULL));
    for (int i = nb_creneaux - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* temp = creneaux[i];
        creneaux[i] = creneaux[j];
        creneaux[j] = temp;
    }

    // Afficher les créneaux horaires disponibles
    afficher_creneaux_disponibles(creneaux, nb_creneaux);

    // Demander à l'utilisateur de choisir un créneau
    int choix;
    printf("Choisissez un creneau horaire (entrez le numero correspondant) : ");
    scanf("%d", &choix);

    // Vérifier si le choix est valide
    if (choix >= 1 && choix <= nb_creneaux) {
        printf("Vous avez choisi le creneau horaire : %s\n", creneaux[choix - 1]);
    } else {
        printf("Choix invalide.\n");
    }

    return 0;
}
