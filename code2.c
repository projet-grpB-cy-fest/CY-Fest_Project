#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define couleur(param) printf("\033[%sm", param)

// Structure pour représenter un siège
typedef struct {
    int ligne;
    int colonne;
    char statut; // 'O' pour libre, 'X' pour réservé
    char categorie;
} Siege;

// Structure pour représenter une salle
typedef struct {
    char *nom;
    char *groupe;
    int prixSieges[3]; // Prix pour les sièges avant, milieu et arrière
    Siege sieges[8][8]; // Tableau de sièges pour la salle
} Salle;

// Fonction pour initialiser une salle
void initialiserSalle(Salle *salle) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            salle->sieges[i][j].ligne = i;
            salle->sieges[i][j].colonne = j;
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
    printf("Plan de la salle %s :\n", salle.nom);
    printf("     01 02 03 04 05 06 07 08\n");
    printf("    +-----------------------+\n");
    for (int i = 0; i < 8; i++) {
        printf("%02d | ", i + 1);
        for (int j = 0; j < 8; j++) {
            if (salle.sieges[i][j].statut == 'O') {
                if (salle.sieges[i][j].categorie == 'A') {
                    couleur("0;34"); // Bleu pour les sièges de catégorie A
                } else if (salle.sieges[i][j].categorie == 'B') {
                    couleur("0;33"); // Jaune pour les sièges de catégorie B
                } else if (salle.sieges[i][j].categorie == 'C') {
                    couleur("0;35"); // Magenta pour les sièges de catégorie C
                }
                printf("%02d ", i * 8 + j + 1);
            } else {
                couleur("0;31"); // Rouge pour les sièges réservés
                printf("X  "); // Affichage d'une croix rouge pour un siège réservé
            }
            couleur("0"); // Réinitialisation de la couleur
        }
        printf("|\n");
    }
    printf("+----------------------------+\n");
}

void afficherMessageBienvenue() {
    couleur("1;35"); // Violet et gras
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*  _       __     __                             *\n");
    printf("* | |     / /__  / /________  ____ ___  ___      *\n");
    printf("* | | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\     *\n");
    printf("* | |/ |/ /  __/ / /__/ /_/ / / / / / /  __/     *\n");
    printf("* |__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/      *\n");
    printf("*                                                *\n");
    printf("*      Bienvenue dans notre grand festival !     *\n");
    printf("*                                                *\n");
    printf("**************************************************\n");
    couleur("0"); // Réinitialisation de la couleur
}


int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));
    
    // Affichage du message de bienvenue
    afficherMessageBienvenue();

    // Définition des salles avec des noms et des groupes de musique
    Salle salles[] = {
        {"L'Arène Électrique", "Led Zeppelin", {60, 45, 30}},
        {"Le Salon Groove", "The Rolling Stones", {50, 40, 35}},
        {"Le Repere Funky", "Queen", {70, 55, 40}},
        {"La Fosse Rock", "AC/DC", {65, 50, 35}}
    };

    // Initialisation des salles
    for (int i = 0; i < sizeof(salles) / sizeof(salles[0]); i++) {
        initialiserSalle(&salles[i]);
    }

    // Affichage des salles disponibles, des groupes qui y jouent et des prix des billets
    printf("Salles disponibles :\n");
    for (int i = 0; i < sizeof(salles) / sizeof(salles[0]); i++) {
        printf("%d. %s\n   Groupe : %s\n   Prix du billet (avant/milieu/arrière) : %d/%d/%d euros\n\n",
               i + 1, salles[i].nom, salles[i].groupe, salles[i].prixSieges[0], salles[i].prixSieges[1], salles[i].prixSieges[2]);
    }

    // Demande à l'utilisateur de choisir une salle
    int choix;
    printf("Dans quelle salle voulez-vous aller ? (1-%d) : ", (int)(sizeof(salles) / sizeof(salles[0])));
    while (scanf("%d", &choix) != 1 || choix < 1 || choix > sizeof(salles) / sizeof(salles[0])) {
        printf("Choix invalide. Veuillez choisir une salle valide : ");
        while (getchar() != '\n'); // Vider le tampon d'entrée
    }

    // Le choix de la salle est valide
    Salle salleChoisie = salles[choix - 1];

    // Demande à l'utilisateur de choisir s'il souhaite la fosse
    int fosse;
    printf("\nFosse ? (0-OUI 1-NON) : ");
    while (scanf("%d", &fosse) != 1 || (fosse != 0 && fosse != 1)) {
        printf("Choix invalide. Veuillez saisir 0 ou 1 : ");
        while (getchar() != '\n'); // Vider le tampon d'entrée
    }

    // Affichage de la salle choisie
    printf("\nVous avez choisi d'aller à %s où %s joue.\n\n", salleChoisie.nom, salleChoisie.groupe);

    // Affichage du plan de la salle
    afficherSalle(salleChoisie, fosse);

    // Demande à l'utilisateur de choisir un siège
    int numeroSiege;
    printf("Quel siège voulez-vous ? (01-64) : ");
    while (scanf("%d", &numeroSiege) != 1 || numeroSiege < 1 || numeroSiege > 64) {
        printf("Siège invalide. Veuillez choisir un siège valide : ");
        while (getchar() != '\n'); // Vider le tampon d'entrée
    }

    // Conversion du numéro de siège en indices de ligne et de colonne
    int ligne = (numeroSiege - 1) / 8;
    int colonne = (numeroSiege - 1) % 8;

    // Le choix de siège est valide
    Siege siegeChoisi = salleChoisie.sieges[ligne][colonne];
    // Vérification de la disponibilité du siège
    if (siegeChoisi.statut == 'X') {
        printf("Ce siège est déjà réservé.\n");
        return 1;
    }

    // Réservation du siège
    salleChoisie.sieges[ligne][colonne].statut = 'X';

    // Affichage du plan de la salle après réservation du siège
    afficherSalle(salleChoisie, fosse);

    // Calcul du prix du siège en fonction de son emplacement
    int prix;
    if (ligne == 0 || ligne == 7) {
        prix = salleChoisie.prixSieges[0]; // Siège avant ou arrière
    } else {
        prix = salleChoisie.prixSieges[1]; // Siège du milieu
    }
    printf("Le prix du billet pour ce siège est de %d euros.\n", prix);

    printf("Merci pour votre achat ! Profitez du concert !\n");

    return 0;
}