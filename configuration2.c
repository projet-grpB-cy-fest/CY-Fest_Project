#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE 100
#define NB_SALLES 3
#define NB_LIGNES 8
#define NB_COLONNES 8

typedef struct {
    char nom_salle[TAILLE];
    char groupe[TAILLE];
    int nb_siege;
    int nb_siege_reserves;
    int prixSieges[3];
    int fosse;
    int creneaux;
    char places[NB_LIGNES][NB_COLONNES];
} Salle;

Salle salles_concert[NB_SALLES]; // Déclaration globale

void initialiserSalles() {
    for (int i = 0; i < NB_SALLES; i++) {
        strcpy(salles_concert[i].nom_salle, ""); // Initialiser les noms de salle à une chaîne vide
    }
}

void better_scan(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Supprimer le '\n' de la fin
}

int better_scan_int(const char *prompt) {
    char buffer[TAILLE];
    better_scan(prompt, buffer, TAILLE);
    return atoi(buffer);
}

int demander_creneaux() {
    // Fonction fictive pour demander les créneaux
    return 1;
}

void initialiserSalle(Salle *salle) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            salle->places[i][j] = 'L'; // 'L' pour Libre
        }
    }
}

void sauvegarde_donnee_salle(char *nom_salle, char *groupe, int nb_siege, int prix_avant, int prix_milieu, int prix_arriere, int fosse, int creneaux) {
    // Fonction fictive pour sauvegarder les données d'une salle
}

void sauvegarde_donnee_salle_modif(char *nom_salle, char *groupe, int nb_siege, int prix_avant, int prix_milieu, int prix_arriere, int fosse, int creneaux) {
    // Fonction fictive pour sauvegarder les données modifiées d'une salle
}

Salle constructeur_Salle() {
    Salle salle;
    better_scan("\nSaisir le nom de la salle: ", salle.nom_salle, TAILLE);
    better_scan("\nSaisir le nom du groupe de musique: ", salle.groupe, TAILLE);
    salle.nb_siege = NB_LIGNES * NB_COLONNES;
    salle.nb_siege_reserves = 0;
    salle.prixSieges[0] = better_scan_int("\nSaisir le prix des sièges avant: ");
    salle.prixSieges[1] = better_scan_int("\nSaisir le prix des sièges milieu: ");
    salle.prixSieges[2] = better_scan_int("\nSaisir le prix des sièges arrière: ");
    do {
        salle.fosse = better_scan_int("\nFosse ? (1-OUI 2-NON): ");
    } while (salle.fosse < 1 || salle.fosse > 2);
    salle.creneaux = demander_creneaux();
    sauvegarde_donnee_salle(salle.nom_salle, salle.groupe, salle.nb_siege, salle.prixSieges[0], salle.prixSieges[1], salle.prixSieges[2], salle.fosse, salle.creneaux);
    initialiserSalle(&salle);

    for (int i = 0; i < NB_SALLES; i++) {
        if (strcmp(salles_concert[i].nom_salle, "") == 0) {
            salles_concert[i] = salle;
            break;
        }
    }
    return salle;
}

void afficherListeSalles(Salle salles[], int nb_salles) {
    printf("\nListe des salles créées:\n");
    for (int i = 0; i < nb_salles; i++) {
        if (strcmp(salles[i].nom_salle, "") != 0) {
            printf("%d. %s\n", i + 1, salles[i].nom_salle);
        }
    }
}

float calculerRatio(Salle salle) {
    return (float)salle.nb_siege_reserves / salle.nb_siege * 100;
}

Salle configuration_Salle(Salle *salle) {
    salle->prixSieges[0] = better_scan_int("\nSaisir le prix des sièges avant: ");
    salle->prixSieges[1] = better_scan_int("\nSaisir le prix des sièges milieu: ");
    salle->prixSieges[2] = better_scan_int("\nSaisir le prix des sièges arrière: ");
    do {
        salle->fosse = better_scan_int("\nFosse ? (1-OUI 2-NON): ");
    } while (salle->fosse < 1 || salle->fosse > 2);
    salle->creneaux = demander_creneaux();
    sauvegarde_donnee_salle_modif(salle->nom_salle, salle->groupe, salle->nb_siege, salle->prixSieges[0], salle->prixSieges[1], salle->prixSieges[2], salle->fosse, salle->creneaux);
    initialiserSalle(salle);
    return *salle;
}

void choixmenu_mode(int mode) {
    int choix_manager, choix_festivalier, choix_salles;

    if (mode == 1) {
        printf("\nMode MANAGER: \n1-Créer une salle \n2-Modifier la configuration d'une salle \n3-État de la salle \n4-Retour au menu principal \n");

        do {
            choix_manager = better_scan_int("\n\nEntrez votre choix (1-4): ");
        } while (choix_manager < 1 || choix_manager > 4);

        switch (choix_manager) {
            case 4:
                printf("\nRetour au menu principal\n");
                choixmenu();
                break;

            case 1:
                printf("\nCréation de salle: \n");
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") == 0) {
                        printf("\nCréation de la salle %d\n", i +1);
                        salles_concert[i] = constructeur_Salle();
                        break;
                    }
                }
                afficherListeSalles(salles_concert, NB_SALLES);
                choixmenu_mode(1);
                break;

            case 2:
                printf("\nConfiguration salle: \n");
                afficherListeSalles(salles_concert, NB_SALLES);
                do {
                    choix_salles = better_scan_int("\nQuelle salle voulez-vous modifier (1-3): ");
                } while (choix_salles <= 0 || choix_salles > NB_SALLES || strcmp(salles_concert[choix_salles - 1].nom_salle, "") == 0);
                salles_concert[choix_salles - 1] = configuration_Salle(&salles_concert[choix_salles - 1]);
                choixmenu_mode(1);
                break;

            case 3:
                printf("\nÉtat salle: \n");
                afficherListeSalles(salles_concert, NB_SALLES);
                printf("\nDétails des salles:\n");
                for (int i = 0; i < NB_SALLES; i++) {
                    if (strcmp(salles_concert[i].nom_salle, "") != 0) {
                        printf("Nom de la salle: %s\n", salles_concert[i].nom_salle);
                        printf("Nombre de sièges réservés: %d\n", salles_concert[i].nb_siege_reserves);
                        printf("Ratio de réservation: %.2f%%\n", calculerRatio(salles_concert[i]));
                    }
                }
                choixmenu_mode(1);
                break;

            default:
                printf("\nErreur de saisie\n");
                choixmenu_mode(1);
                break;
        }
    }

    if (mode == 2) {
        printf("\nMenu FESTIVALIER: \n1-Réservation \n2-Retour au menu principal \n");

        do {
            choix_festivalier = better_scan_int("\n\nEntrez votre choix (1-2): ");
        } while (choix_festivalier < 1 || choix_festivalier > 2);

        switch (choix_festivalier) {
            case 2:
                printf("\nRetour au menu principal\n");
                choixmenu();
                break;

            case 1:
                // Logique de réservation à ajouter ici
                break;

            default:
                printf("\nErreur de saisie\n");
                choixmenu_mode(2);
                break;
        }
    }
}

void choixmenu() {
    int choix;
    printf("\nMenu Principal: \n1-Mode Manager \n2-Mode Festivalier \n3-Quitter\n");
    do {
        choix = better_scan_int("\nEntrez votre choix (1-3): ");
    } while (choix < 1 || choix > 3);
    choixmenu_mode(choix);
}

int main() {
    initialiserSalles();
    choixmenu();
    return 0;
}
