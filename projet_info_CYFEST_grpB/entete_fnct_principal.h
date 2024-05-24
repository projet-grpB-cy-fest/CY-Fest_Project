//Inclusions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Appele fichier.h du programme fnct_heure.c et fnct_sauv_donnee.c
#include "entete_heure.h" 
#include "entete_sauv_donnee.h"

//Definitions
#define couleur(param) printf("\033[%sm", param)
#define TAILLE 50
#define NB_LIGNES 8
#define NB_COLONNES 8
#define NB_SALLES 3

//Structures
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
    float prixSieges[3];  // Prix pour les sièges avant, milieu et arrière
    Siege sieges[NB_LIGNES][NB_COLONNES]; // Tableau de sièges pour la salle
    int fosse;
    struct tm heure_fin;
} Salle;

//Fonctions
void initialiserSalle(Salle *salle);//Fonction pour initialiser une salle
void afficherSalle(Salle salle, int fosse);//Fonction pour afficher le plan d'une salle
int better_scan(char *message, char *result, int size);//Fonction pour scanner une chaîne de caractères
int better_scan_int(char *message);//Fonction pour scanner un entier
double calculerRatio(int nb_sieges_reserves, int nb_sieges_total);//Fonction pour calculer le ratio de réservation (Mode Manager)
void afficherRatioReservation(Salle salles[], int nb_salles);//Fonction pour afficher le ratio de réservation pour chaque salle (Mode Manager)
Salle constructeur_Salle();//Fonction pour créer une salle (Mode Manager)
Salle configuration_Salle(Salle salle);//Fonction pour modifier la configuration d'une salle (Mode Manager)
void gestionFestivalier(Salle salles[]);//Fonction pour réserver un siége (Mode Festivalier)

