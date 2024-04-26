#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure pour représenter la salle de concert
typedef struct {
    char nom[50];
    int capacite;
    char lieu[50];
    int prix_avant;  // Prix des sièges avant
    int prix_milieu; // Prix des sièges au milieu
    int prix_fin;    // Prix des sièges à l'arrière
} SalleConcert;

// Structure pour représenter un concert
typedef struct{
    char nom_artiste[50];
    char date[20];
    char heure[10];
} Concert;

// Fonction pour créer une nouvelle salle de concert avec des caractéristiques aléatoires
SalleConcert creer_salle_de_concert(char *nom, int capacite, char *lieu) {
    SalleConcert nouvelle_salle;
    strcpy(nouvelle_salle.nom, nom);
    nouvelle_salle.capacite = capacite;
    strcpy(nouvelle_salle.lieu, lieu);
    // Génération de prix aléatoires pour les différentes catégories de sièges
    nouvelle_salle.prix_avant = rand() % 50 + 50;   // Prix entre 50 et 100
    nouvelle_salle.prix_milieu = rand() % 40 + 70;  // Prix entre 70 et 110
    nouvelle_salle.prix_fin = rand() % 30 + 90;     // Prix entre 90 et 120
    return nouvelle_salle;
}

// Fonction pour attribuer un concert à une salle avec une date et une heure spécifiques
void attribuer_concert(SalleConcert *salle, Concert concert) {
    printf("Attribution du concert '%s' à la salle '%s'\n", concert.nom_artiste, salle->nom);
    printf("Date : %s, Heure : %s\n", concert.date, concert.heure);
}

// Fonction pour modifier les configurations d'une salle donnée
void modifier_configuration_salle(SalleConcert *salle, int nouvelle_capacite, char *nouveau_lieu) {
    salle->capacite = nouvelle_capacite;
    strcpy(salle->lieu, nouveau_lieu);
    printf("Les configurations de la salle '%s' ont ete modifiees.\n", salle->nom);
}

// Fonction pour consulter les statistiques sur l'état d'une salle spécifique
void consulter_statistiques_salle(SalleConcert salle) {
    printf("Statistiques de la salle '%s':\n", salle.nom);
    printf("Capacite : %d\n", salle.capacite);
    printf("Lieu : %s\n", salle.lieu);
    printf("Prix des sieges avant : %d\n", salle.prix_avant);
    printf("Prix des sieges au milieu : %d\n", salle.prix_milieu);
    printf("Prix des sieges a l'arriere : %d\n", salle.prix_fin);
}

int main() {
    // Initialisation du générateur de nombres aléatoires avec une graine
    srand(time(NULL));

    // Création de trois salles de concert avec des caractéristiques aléatoires
    SalleConcert salle1 = creer_salle_de_concert("Salle A", 200, "Place X");
    SalleConcert salle2 = creer_salle_de_concert("Salle B", 150, "Place Y");
    SalleConcert salle3 = creer_salle_de_concert("Salle C", 300, "Place Z");

    // Attribution d'un concert à la salle 1
    Concert concert1 = {"Les Jonas Brothers", "2024-05-01", "20:00"};
    attribuer_concert(&salle1, concert1);

    // Modification des configurations de la salle 2
    modifier_configuration_salle(&salle2, 180, "Place W");

    // Consultation des statistiques des trois salles
    consulter_statistiques_salle(salle1);
    consulter_statistiques_salle(salle2);
    consulter_statistiques_salle(salle3);
    // Demander à l'utilisateur de choisir une salle de concert
    int choix_salle;
    printf("Choisissez une salle de concert :\n");
    printf("1. %s\n", salle1.nom);
    printf("2. %s\n", salle2.nom);
    printf("3. %s\n", salle3.nom);
    scanf("%d", &choix_salle);

    // Afficher les statistiques de la salle choisie
    switch (choix_salle) {
        case 1:
            consulter_statistiques_salle(salle1);
            break;
        case 2:
            consulter_statistiques_salle(salle2);
            break;
        case 3:
            consulter_statistiques_salle(salle3);
            break;
        default:
            printf("Choix invalide.\n");
            break;
    }

    return 0;
}
