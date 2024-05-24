#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Appele fichier.h du programme fnct_principal.c
#include "entete_fnct_principal.h"

//Fonction pour afficher les créneaux disponible
void afficher_creneaux_disponibles(char* creneaux[], int nb_creneaux) {
    printf("Creneaux horaires disponibles pour le 27 juin :\n");
    for (int i = 0; i < nb_creneaux; i++) {
        printf("%d. %s\n", i+1, creneaux[i]);
    }
}

//Fonction pour demander à l'utilisateur quel créneaux il souhaite
int demander_creneaux(){
    //Initialisation des créneaux horaires disponibles
    char* creneaux[] = {"9:00-10:00", "10:00-11:00", "11:00-12:00", "13:00-14:00", "14:00-15:00", "15:00-16:00"};
    int nb_creneaux = sizeof(creneaux) / sizeof(creneaux[0]);

    //Afficher les créneaux horaires disponibles
    afficher_creneaux_disponibles(creneaux, nb_creneaux);

    //Demander à l'utilisateur de choisir un créneau
    int choix=better_scan_int("Choisissez un creneau horaire (entrez le numero correspondant): ");

    //Vérifie si le choix est valide
    if (choix >= 1 && choix <= nb_creneaux) {
        printf("Vous avez choisi le creneau horaire : %s\n", creneaux[choix - 1]);
    } else {
        printf("Choix invalide.\n");
    }
    return choix;
}

