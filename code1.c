#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define couleur(param) printf("\033[%sm", param)
#define TAILLE 50
#define NB_LIGNES 8
#define NB_COLONNES 8

// Structure pour représenter un siège
typedef struct {
    int numero;
    char statut; // 'O' pour libre, 'X' pour réservé
    char categorie;
} Siege;

// Structure pour représenter une salle
typedef struct {
    char nom_salle[TAILLE];
    char groupe[TAILLE];
    int nb_siege;
    int nb_siege_reserves;
    int prixSieges[3];  // Prix pour les sièges avant, milieu et arrière
    Siege sieges[NB_LIGNES][NB_COLONNES]; // Tableau de sièges pour la salle
} Salle;

// Fonction pour initialiser une salle
void initialiserSalle(Salle *salle) {
    int numero = 1;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            salle->sieges[i][j].numero = numero++;
            salle->sieges[i][j].statut = 'O'; // Tous les sièges sont libres au début
            if (i < 3) {
                salle->sieges[i][j].categorie = 'A'; // Première rangée, catégorie A
            } else if (i < 6) {
                salle->sieges[i][j].categorie = 'B'; // Deuxième rangée, catégorie B
            } else {
                salle->sieges[i][j].categorie = 'C'; // Dernière rangée, catégorie C
            }
        }
    }
}

// Fonction pour afficher le plan d'une salle
void afficherSalle(Salle salle, int fosse) {
    printf("Plan de la salle %s :\n", salle.nom_salle);
    printf("     01 02 03 04 05 06 07 08\n");
    printf("    +-----------------------+\n");
    for (int i = 0; i < NB_LIGNES; i++) {
        printf("%02d | ", i + 1);
        for (int j = 0; j < NB_COLONNES; j++) {
            if (fosse == 0 && i < 3) {
                printf("   "); // Affiche un espace vide pour la fosse
            } else {
                if (salle.sieges[i][j].statut == 'O') {
                    if (salle.sieges[i][j].categorie == 'A') {
                        couleur("0;34"); // Bleu pour les sièges de catégorie A
                    } else if (salle.sieges[i][j].categorie == 'B') {
                        couleur("0;33"); // Jaune pour les sièges de catégorie B
                    } else if (salle.sieges[i][j].categorie == 'C') {
                        couleur("0;35"); // Magenta pour les sièges de catégorie C
                    }
                    printf("%02d ", salle.sieges[i][j].numero);
                } else {
                    couleur("0;31"); // Rouge pour les sièges réservés
                    printf("X  "); // Affichage d'une croix rouge pour un siège réservé
                }
            }
            couleur("0"); // Réinitialisation de la couleur
        }
        printf("|\n");
    }
    printf("+----------------------------+\n");
}

// Fonction pour afficher un message de bienvenue
void afficherMessageBienvenue() {
    couleur("1;35"); // Violet et gras
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*  _       __     __                             *\n");
    printf("* | |     / /__  / /________  ____ ___  ___      *\n");
    printf("* | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\     *\n");
    printf("* | |/ |/ /  __/ / /__/ /_/ / / / / /  __/     *\n");
    printf("* |__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/      *\n");
    printf("*                                                *\n");
    printf("*      Bienvenue dans notre grand festival !     *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    couleur("0"); // Réinitialisation de la couleur
}

// Fonction pour scanner une chaîne de caractères
int better_scan(char *message, char *result, int size) {
    printf("%s", message);
    fgets(result, size, stdin);
    // Remplacer le '\n' final par '\0'
    if (result[strlen(result) - 1] == '\n') {
        result[strlen(result) - 1] = '\0';
    }
    return 1; // Retourner toujours 1, car fgets ne retourne pas d'erreur ici
}

// Fonction pour scanner un entier
int better_scan_int(char *message) {
    int value;
    printf("%s", message);
    scanf("%d", &value);
    while (getchar() != '\n')
        ; // Vider le buffer d'entrée
    return value;
}

// Fonction pour calculer le ratio de réservation
double calculerRatio(int nb_sieges_reserves, int nb_sieges_total) {
    return (double)nb_sieges_reserves / nb_sieges_total * 100;
}

// Fonction pour créer une salle (Mode Manager)
Salle constructeur_Salle() {
    Salle salle;
    better_scan("Saisir le nom de la salle : ", salle.nom_salle, TAILLE);
    better_scan("Saisir le nom du groupe de musique : ", salle.groupe, TAILLE);
    salle.nb_siege = NB_LIGNES * NB_COLONNES; // Fixé à 64 sièges pour toutes les salles
    salle.nb_siege_reserves = 0; // Initialisation du nombre de sièges réservés
    salle.prixSieges[0] = better_scan_int("Saisir le prix des sièges avant : ");
    salle.prixSieges[1] = better_scan_int("Saisir le prix des sièges milieu : ");
    salle.prixSieges[2] = better_scan_int("Saisir le prix des sièges arrière : ");
    initialiserSalle(&salle);
    return salle;
}

void gestionFestivalier(Salle salles[]) {
    // Affichage des salles disponibles, des groupes qui y jouent et des prix des billets
    printf("Salles disponibles :\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s\n   Groupe : %s\n   Prix du billet (avant/milieu/arrière) : %d/%d/%d euros\n\n",
               i + 1, salles[i].nom_salle, salles[i].groupe,
               salles[i].prixSieges[0], salles[i].prixSieges[1],
               salles[i].prixSieges[2]);
    }

    // Demande à l'utilisateur de choisir une salle
    int choix;
    printf("Dans quelle salle voulez-vous aller ? (1-4) : ");
    while (scanf("%d", &choix) != 1 || choix < 1 || choix > 4) {
        printf("Choix invalide. Veuillez choisir une salle valide (1-4) : ");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
    }
    Salle *salleChoisie = &salles[choix - 1];

    // Demande à l'utilisateur de choisir s'il souhaite la fosse
    int fosse;
    printf("\nFosse ? (0-OUI 1-NON) : ");
    while (scanf("%d", &fosse) != 1 || (fosse != 0 && fosse != 1)) {
        printf("Choix invalide. Veuillez saisir 0 ou 1 : ");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
    }

    int prix_a_payer = 0;
    if (fosse == 0) {
        // L'utilisateur choisit la fosse
        prix_a_payer = 2 * salleChoisie->prixSieges[0];
        printf("Vous avez choisi la fosse. Le prix à payer est de %d euros.\n", prix_a_payer);
    } else {
        // Affichage de la salle choisie
        afficherSalle(*salleChoisie, fosse);

        // Réservation de sièges par le festivalier
        int reserver;
        printf("Voulez-vous réserver un siège ? (1-OUI, 0-NON) : ");
        while (scanf("%d", &reserver) != 1 || (reserver != 0 && reserver != 1)) {
            printf("Choix invalide. Veuillez saisir 1 pour OUI ou 0 pour NON : ");
            while (getchar() != '\n')
                ; // Vider le tampon d'entrée
        }

        while (reserver == 1) {
            // Demande à l'utilisateur de choisir un siège
            int numeroSiege;
            printf("Quel siège voulez-vous ? (01-64) : ");
            while (scanf("%d", &numeroSiege) != 1 || numeroSiege < 1 || numeroSiege > 64) {
                printf("Siège invalide. Veuillez choisir un siège valide : ");
                while (getchar() != '\n')
                    ; // Vider le tampon d'entrée
            }

            // Conversion du numéro de siège en indices de ligne et de colonne
            int ligne = (numeroSiege - 1) / 8;
            int colonne = (numeroSiege - 1) % 8;

            // Vérification de la disponibilité du siège
            if (salleChoisie->sieges[ligne][colonne].statut == 'X') {
                printf("Ce siège est déjà réservé.\n");
            } else {
                // Réservation du siège
                salleChoisie->sieges[ligne][colonne].statut = 'X';
                salleChoisie->nb_siege_reserves++;

                // Calcul du prix en fonction de la catégorie
                if (salleChoisie->sieges[ligne][colonne].categorie == 'A') {
                    prix_a_payer += salleChoisie->prixSieges[0];
                } else if (salleChoisie->sieges[ligne][colonne].categorie == 'B') {
                    prix_a_payer += salleChoisie->prixSieges[1];
                } else {
                    prix_a_payer += salleChoisie->prixSieges[2];
                }

                // Affichage du plan de la salle après réservation du siège
                afficherSalle(*salleChoisie, fosse);

                // Demande si l'utilisateur veut réserver un autre siège
                printf("Voulez-vous réserver un autre siège ? (1-OUI, 0-NON) : ");
                while (scanf("%d", &reserver) != 1 || (reserver != 0 && reserver != 1)) {
                    printf("Choix invalide. Veuillez saisir 1 pour OUI ou 0 pour NON : ");
                    while (getchar() != '\n')
                        ; // Vider le tampon d'entrée
                }
            }
        }

        // Affichage du prix total à payer
        printf("Le prix total à payer est de %d euros.\n", prix_a_payer);
    }

    // Calcul et affichage du ratio de réservation
    double ratio = calculerRatio(salleChoisie->nb_siege_reserves, salleChoisie->nb_siege);
    printf("Le ratio de réservation est de %.2f%%\n", ratio);

    // Remerciement
    printf("Merci pour votre réservation !\n");
}

int main() {
    afficherMessageBienvenue();

    // Demande à l'utilisateur de choisir entre le mode Manager et le mode Festivalier
    int mode;
    printf("Choisissez un mode : (1-Manager, 2-Festivalier) : ");
    while (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
        printf("Choix invalide. Veuillez saisir 1 pour Manager ou 2 pour Festivalier : ");
        while (getchar() != '\n')
            ; // Vider le tampon d'entrée
    }

    // Mode Manager
    if (mode == 1) {
        Salle salles[4];
        for (int i = 0; i < 4; i++) {
            printf("Création de la salle %d\n", i + 1);
            salles[i] = constructeur_Salle();
        }
    }
    // Mode Festivalier
    else if (mode == 2) {
        Salle salles[4];
        for (int i = 0; i < 4; i++) {
            printf("Création de la salle %d\n", i + 1);
            salles[i] = constructeur_Salle();
        }
        gestionFestivalier(salles);
    }

    return 0;
}