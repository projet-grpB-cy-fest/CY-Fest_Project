//Inclusions
#include <stdio.h>
#include <stdlib.h>
//Appele fichier.h du programme fnct_principal.c
#include "entete_fnct_principal.h"

//Fonctions
void choixmenu();//Fonction pour afficher le menu principale
void choixmenu_mode(int mode);//Fonction pour afficher le menu selon le mode choisi
void afficherListeSalles(Salle salles[], int nb_salles);//Fonction pour afficher la liste des salles créées pour la configuration